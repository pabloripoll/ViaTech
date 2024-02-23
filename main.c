#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int error=0;
    // VALIDATION
    if(argc == 1 || argc == 2){
        printf("Error - To few arguments! \n");
        error=1;
    }
    if(argc > 3){
        printf("Error - Exceeded arguments! \n");
        error=1;
    }
    if(error == 1){
        printf("Program expects two arguments: \n");
        printf("1) Root directory path.\n");
        printf("2) Days to count (integer) to make the purge.\n");
        printf("\n");
        return 1;
    }
    // VALIDATION OF DIRECTORY
    DIR* dir=opendir(argv[1]);
    if (!dir) {
        printf("Program expects two valid arguments: \n");
        printf("1) Root directory path doesn't exist or mismatch. [FAIL]\n");
        printf("2) Days to count (integer) to make the purge.\n");
        printf("\n");
        return 1;
    }
    // VALIDATION OF DAY
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int count=atoi(argv[2]);
    if (!count) {
        printf("Program expects two valid arguments: \n");
        printf("1) Root directory path: %s [O.K.]\n", argv[1]);
        printf("2) Days to count (integer) to make the purge. [FAIL]\n");
        printf("\n");
        return 1;
    }
    if (count < 1 || count > 31) {
        printf("Program expects two valid arguments: \n");
        printf("1) Root directory path: %s [O.K.]\n", argv[1]);
        printf("2) Days to count value must be between (1) and (31). [FAIL]\n");
        printf("\n");
        return 1;
    }
    // EXECUTION
    // OS SYSTEM
    #if defined(_WIN32) || defined(_WIN64)
        // Windows code
        char cd[1];
        sprintf(cd,"%s", "\\");
    #else
        // GNU/Linux code
        char cd[1];
        sprintf(cd,"%s", "/");
    #endif
    // VALUES
    int y_int=tm.tm_year + 1900;
    int m_int=tm.tm_mon + 1;
    int d_int=tm.tm_mday;
    int dl_int=tm.tm_mday - count;
    // INFO
    printf("Executing PURGE...\n");
    printf("Location: %s\n", argv[1]);
    printf("Today directory's name value: %d%02d%02d\n", y_int, m_int, d_int);
    printf("Purging directories name value older than %d%02d%02d (%s days)\n", y_int, m_int, dl_int, argv[2]);
    printf("\n");
    // PROCEEDING
    int i;
    char target[256];
    for(i = 1; i < 32; ++i){
        struct dirent *de;
        if(i >= dl_int){
            target[0] = (char) 0;
            sprintf(target,"%s%s%d%02d%02d", argv[1], cd, y_int, m_int, i);
            DIR *dr = opendir(target);
            if(dr){
                printf("%s [KEEP]\n", target);
            }
        }
        if(i < dl_int){
            target[0] = (char) 0;
            sprintf(target,"%s%s%d%02d%02d", argv[1], cd, y_int, m_int, i);
            DIR *dr = opendir(target);
            if(!dr){
                continue;
            }
            int deleted = 0;
            char cmd[256] = {0};
            sprintf(cmd, "rm -rf %s 2>&1", target);
            deleted=system(cmd);
            if(deleted == 0){
                printf("%s [DELETED]\n", target);
            }else{
                printf("%s [FAIL]\n", target);
            }
        }
    }
    printf("\n");
    return 0;
}