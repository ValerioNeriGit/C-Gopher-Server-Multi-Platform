#ifndef GOPHER_LINUX_MEMORY_MAPPING_H
#define GOPHER_LINUX_MEMORY_MAPPING_H
int linux_memory_mapping(void *params);
int SendFileMapped(int write_fd, char *fileToSend, int fileSize);
int fileSize(int fd);
void * l_sendFile(void *send_args);
#endif //GOPHER_LINUX_MEMORY_MAPPING_H
