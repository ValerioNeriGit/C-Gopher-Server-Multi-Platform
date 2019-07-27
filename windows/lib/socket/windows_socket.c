#include <windows.h>


#include <winsock2.h>
#include <stdio.h>
#include <io.h>
#include <unistd.h>
#include <protocol.h>
#include <windows_protocol.h>
#include <errno.h>
#include <ws2tcpip.h>
#include <excpt.h>
#include "utils.h"
#include "windows_socket.h"
#include "winThread.h"
#include "definitions.h"
#include "files_interaction.h"
#include "socket.h"

int end_server(SOCKET fd){
    shutdown(fd, 2);
    closesocket(fd);
    return 0;
}
int windows_socket_runner(struct Configs *configs) {
    HANDLE thread;
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    /* socket */
    fd_set read_fds;
    fd_set working_set;

    if (0 != WSAStartup(MAKEWORD(2, 2), &WSAData)) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return -1;
    }

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > server) {
        printf("Errore creazione socket");
        perror("Server = socket ");
    }

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(configs->port_number);

    bind(server, (SOCKADDR *) &serverAddr, sizeof(serverAddr));
    listen(server, 0);

    printf("Listening for incoming connections...");

    // int accept_fd;
    int clientAddrSize = sizeof(clientAddr);


    // new struct for thread/process
    // TODO testare e semplificare
    struct Configs c2;
    struct Configs *n;
    c2.reset_config = NULL;
    n = &c2;
    ut_clone_configs(configs, n);

    struct ThreadArgs args;
    args.configs = *n;


    FD_ZERO(&read_fds);
    FD_SET(server, &read_fds);
    int n_ready;
    //Windows
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 5;
    while (MAX_CONNECTIONS_ALLOWED) {
        memcpy(&working_set, &read_fds, sizeof(read_fds));
        printf("\n%s %d\n", "server ->", server);
        // rc =
        // # richieste di connessione
        if ((n_ready = select(server + 1, &working_set, NULL, NULL, &timeout)) < 0) {
            if (errno == EINTR) continue;
            else {
                perror("select");
                exit(1);
            }
        }

        if (n_ready == 0) {
            // printf("  select() timed out.  End program.\n");
            perror("select");
            if (configs->reset_config != NULL) {
                //end_server(fd_server);
                // printf("Reset socket break\n");
                // printf("SONO SHUTDOWN %d\n", end_server(server));
                return -1;
            }

            printf("Reset socket continue %ls \n", configs->reset_config);
            timeout.tv_sec = 2;
            timeout.tv_usec = 5;
            continue;
        }

        if (FD_ISSET(server, &working_set)) { /* richiesta proveniente da client TCP */
            if ((client = accept(server, (SOCKADDR *) &clientAddr, &clientAddrSize)) < 0) {
                if (errno == EINTR) continue;
                else {
                    perror("accept");
                    exit(1);
                }
            }
            args.ip_client = inet_ntoa(clientAddr.sin_addr);
            printf("Client connected!\n");
            printf("IP address is: %s\n", args.ip_client);
            args.fd = client;

            // handle_request((PVOID) &args);
            // TODO cambiare con _beginthread
            if (0 != (thread = CreateThread(NULL, 0, handle_request, (PVOID) &args, 0, NULL))) {
                printf("funziona\n");
            }
            CloseHandle(thread);
        }
    }

}

DWORD WINAPI handle_request(void *params) {

    // TODO thread detached
    char *buf;
    char *path;
    struct ThreadArgs *args;
    args = (struct ThreadArgs *) params;

    printf("%s\n", "Running in thread - handle request");
    printf("args: %d\n", args->fd);

    socket_read_request(args, &buf); // fill the buffer with the request

    printf("%s\n", buf);

    socket_resolve_selector(args, buf, &path); // parse the request

    // todo fix resolve_selector come su linux
    printf("full path %s \n", path);

    socket_manage_files(path, buf, args); // send response
    printf("PRIMA DI CLEAN");

    clean_request(path, buf, args);
    printf("DOPO CLEAN");
    return 0;
}


DWORD WINAPI w_sendFile(PVOID args) {

    struct sendArgs *send_args = (struct sendArgs *) args;
    int fd_client = send_args->fd;
    char *message_to_send = send_args->buff;

    int bufferSize = 512;
    char buffer[bufferSize];
    int sendPosition = 0;
    int message_len = strlen(message_to_send);
    while (message_len > 0) {
        int chunkSize = message_len > bufferSize ? bufferSize : message_len;
        memcpy(buffer, message_to_send + sendPosition, chunkSize);
        chunkSize = send(fd_client, buffer, chunkSize, 0);
        if (chunkSize == -1) { break; }
        message_len -= chunkSize;
        sendPosition += chunkSize;
    }
    return 0;
}

