#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <unistd.h>
#include <stdlib.h>


#include "definitions.h"
#include "protocol.h"
#include "utils.h"
#include "config_file.h"
#include "files_interaction.h"

#if defined(__unix__) || defined(__APPLE__)

#include <signal.h>
#include "linux_files_interaction.h"
#include "files_interaction.h"
#include "linux_thread.h"
#include "linux_socket.h"
#include "linux_signals.h"

#endif

#ifdef _WIN32


#include <windows.h>
#include "windows_socket.h"
#include "windows_events.h"

#endif
// reformat Sh + ò
// comment Sh + ù
// run Sh + Enter
// Ctrl + Enter

int main(int argc, char *argv[]) {

    printf("%s\n", "Gopher start ...");

    //perror("main#");

#ifdef _WIN32

    printf("SONO ARGC%d\n", argc);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (CreateProcess("C:\\Users\\andrea\\CLionProjects\\gopher5\\gopher-project\\cmake-build-debug\\gopherWinSubProcess.exe",
                      "readPipe", NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
        //WaitForSingleObject(pi.hProcess, INFINITE);
    }else {
        perror("create process is failed");
    }




#endif
    struct Configs c;
    c.reset_config = NULL;
    configs = &c;


    // configs.root_dir = malloc(50 * sizeof(char));
    // chiamata alla lettura del file di configurazione
    //
    printf("PID: %ld  PPID: %ld\n", (long) getpid());

    //
    conf_parseConfigFile(CONFIGURATION_PATH, configs);
    printf("\n sono conf.rootdir %s\n", configs->root_dir);
    if (conf_read_opt(argc, argv, configs) != 0) return 1;
    /*
    configs.port_number = 7070;
    configs.mode_concurrency=1;
    configs.root_dir="/sda";
    */
    printf("port:%d mode:%d %lu dir:%s\n", configs->port_number, configs->mode_concurrency, strlen(configs->root_dir),
           configs->root_dir);


#if defined(__unix__) || defined(__APPLE__)

    if (signal(SIGHUP, signal_sighup_handler) == SIG_ERR){
        perror("Signal");
    }

    printf("%c \n", getGopherCode("C:/Users/valerio/file.png"));

    start_mutex();

    linux_socket(configs);
    while (true) {

        c.reset_config = NULL;
        configs = &c;
        conf_parseConfigFile("../gopher_server_configuration.txt", configs);

        linux_socket(configs);
    }

    close_mutex();

    //pthread_t t_id;

    //thr_pthread_create(&t_id, &thr_test_func, (void *) "lol");
    //sleep(2);

#endif
#ifdef _WIN32


    // BOOL running = TRUE;
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        printf("\nERROR: Could not set control handler");
        return 1;
    }

    while (true) {
        windows_socket_runner(configs);
        c.reset_config = NULL;
        configs = &c;
        conf_parseConfigFile("../gopher_server_configuration.txt", configs);

    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

#endif
    //printf("%s", configs.root_dir);
    if (configs->used_OPTARG == false) {
        free(configs->root_dir);
    }
    //sleep(2);
    //return 0;
#if defined(__unix__) || defined(__APPLE__)

    if (M_THREAD == configs->mode_concurrency) {
        sleep(1);
        pthread_exit(NULL);
    }
#endif

    exit(0);
    //pthread_exit(&ret);
}
