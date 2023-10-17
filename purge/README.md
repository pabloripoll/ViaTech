# CMD

## Requirements
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

### Execution
```
C:\> ./PURGE.CMD
```

## Task
It is needed to run a script such as “PURGE.CMD” with a parameter of parent path and another parameter with number of days to keep e.g. 7 and for any subfolders (and their contents) with a folder name that represents a date older than 7 days is then deleted.

In the path of D:/TEST there are subfolders accumulating daily file e.g.
```
D:/TEST/20231015
D:/TEST/20231014
D:/TEST/20231013
D:/TEST/20231012
D:/TEST/20231011
D:/TEST/20231010
D:/TEST/20231009
D:/TEST/20231008
D:/TEST/20231007
```

Which would leave just:
```
D:/TEST/20231015
D:/TEST/20231014
D:/TEST/20231013
D:/TEST/20231012
D:/TEST/20231011
D:/TEST/20231010
D:/TEST/20231009
```

Probably classic stuff but I don’t have time to do this and thought you may enjoy a simple(ish) task! This has to be delivered as a windows CMD script that takes a command line parameter so I can run:
```
PURGE.CMD D:/TEST 7
```

## Sources

Windows
```
https://stackoverflow.com/questions/51054/batch-file-to-delete-files-older-than-n-days
https://stackoverflow.com/questions/51556513/deleting-subfolder-and-files-in-window-through-cmd-and-timestamp-backup
https://in.indeed.com/career-advice/career-development/how-to-delete-a-file-using-cmd
https://superuser.com/questions/173859/how-can-i-delete-all-files-subfolders-in-a-given-folder-via-the-command-prompt
https://www.easeus.com/computer-instruction/delete-files-older-than-x-days.html
https://answers.microsoft.com/en-us/windows/forum/all/delete-files-with-too-long-file-names/461e321e-2ecb-4b82-b49a-6ee9113bfd32
https://superuser.com/questions/932515/how-to-delete-files-with-specified-text-in-their-names
https://www.google.com/search?q=windows+cmd+get+YEAR+MONTH+AND+DAY
https://stackoverflow.com/questions/3472631/how-do-i-get-the-day-month-and-year-from-a-windows-cmd-exe-script
https://superuser.com/questions/315984/how-to-get-the-date-in-a-batch-file-in-a-predictable-format
```

C Program
```
How to Build / Compile and Run a C Program in Command Prompt (cmd) on Windows 10: https://www.youtube.com/watch?v=zQtCsiaeiIE
https://ss64.com/nt/rd.html
https://www.google.com/search?q=windows+c+unlink+directories+inside+directory
https://www.geeksforgeeks.org/how-to-detect-operating-system-through-a-c-program/
https://www.google.com/search?q=c+program+if+windows+system+do
https://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c
https://www.w3schools.com/c/c_strings.php
https://www.includehelp.com/c-programs/remove-an-empty-directory-using-rmdir-function.aspx
https://www.includehelp.com/c-programs/remove-an-empty-directory.aspx?ref=rp
https://www.includehelp.com/c-programs/remove-a-non-empty-directory-using-the-system-function.aspx?ref=rp
https://stackoverflow.com/questions/32661538/how-to-force-deletion-of-file-in-c
https://stackoverflow.com/questions/5467725/how-to-delete-a-directory-and-its-contents-in-posix-c
https://stackoverflow.com/questions/52135961/delete-directory-in-c
https://stackoverflow.com/questions/2256945/removing-a-non-empty-directory-programmatically-in-c-or-c
https://stackoverflow.com/questions/7331056/how-to-delete-a-folder-and-all-contents-using-a-bat-file-in-windows
https://stackoverflow.com/questions/20159122/how-to-silently-delete-files-with-a-bat-file
https://www.freecodecamp.org/news/cmd-delete-folder-how-to-remove-files-and-folders-in-windows/
https://www.programiz.com/c-programming/c-break-continue-statement
```