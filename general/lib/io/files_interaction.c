#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "utils.h"
#include "files_interaction.h"
#include "ut_dict.h"
#include "definitions.h"
int file_exist(char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0); // ritorna diverso da zero se vero
}

int file_type(char *filename) {
    struct stat s;
    if (stat(filename, &s) == 0) {
        if (s.st_mode & S_IFDIR) {
            return FILES_IS_DIRECTORY;
        } else if (s.st_mode & S_IFREG) {
            return FILES_IS_REG_FILE;
        } else {
            return FILES_IS_UNMANAGED_FILE;
        }
    } else {
        return FILES_NOT_EXIST;
    }
}

int write_log_accessFile(char *string, FILE *fp) {

    if (Assert_nb(fp != NULL, "Error opening file.")) {
        return 1;
    }
    fprintf(fp, "%s", string);
    return 0;
}





