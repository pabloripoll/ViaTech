# Directory Purge - Windows

This small program became from an email request for support for a [Windows Server](https://www.microsoft.com/es-es/windows-server) and I found it good to share with you.

Objetives:
```
Hi Pablo,

For Monday, could I ask you to look into something completely different but which will help us anyway.

On a windows machine, I want to be able to run a CMD script which will save some files in a folder that has a date stamp filename e.g. 20231015

So… What I need is another script (CMD file) that will accept the parent path as a parameter and only keep the subfolders that have date filenames up to N days in the past (any subfolder with a dated name older than that is deleted).

Example:
I have a path of D:/TEST
And inside that there are subfolders accumulating daily e.g.

D:/TEST/20231015
D:/TEST/20231014
D:/TEST/20231013
D:/TEST/20231012
D:/TEST/20231011
D:/TEST/20231010
D:/TEST/20231009
D:/TEST/20231008
D:/TEST/20231007
(you get the idea!)

Now I want to run a script such as “PURGE.CMD” with a parameter of parent path and another parameter with number of days to keep e.g. 7
and for any subfolders (and their contents) with a folder name that represents a date older than 7 days is then deleted.
Which would leave just:

D:/TEST/20231015
D:/TEST/20231014
D:/TEST/20231013
D:/TEST/20231012
D:/TEST/20231011
D:/TEST/20231010
D:/TEST/20231009

Probably classic stuff but I don’t have time to do this and thought you may enjoy a simple(ish) task!

This has to be delivered as a windows CMD script that takes a command line parameter so I can run:

PURGE.CMD D:/TEST 7

Cheers,
M.
```

## Development

### Requirements

Check if local machine has GCC compiler as the fllowing example which should output:
```
C:\> gcc --version

gcc (Windows 10.2.0-14) 10.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### Program Compilation
```
C:\> gcc -o PURGE.CMD main.c
```

### Execution command
```
C:\> ./PURGE.CMD
```

Program
```c
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

```