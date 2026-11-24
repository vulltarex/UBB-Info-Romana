# Programming log/notes
---
## Commands and flags/parameters
***
### Navigation and file/directory management

* ls - list directory contents
    - -a - list all (inlcuding hidden) files
    - -l - list with details
    - -lh - list with human readable file size
    - -lS - list files sorted by size
    - -lt - list files sorted by modification time
    - -R - list recursively (list contents of directories inside directories)
    - ls -d */ list directories

* cd - change directory
    - cd .. - go up one directory
    - cd /usr/local/bin - absolute path
    - cd Documents/Projects - relative path
    - cd - -> previous directory
    - cd ~ -> go to home directory

* mkdir dir1 dir2 dir3  - create directories
    - -p dir1/dir2/dir3 - create parent directories if they don't exist
    - -m 755 folder - create directory with specific permissions
    - -v folder - create directory and show what's being done

* pwd - print working directory

* cp - copy files or directories
    - cp file1.txt file2.txt 
    - cp -r dir1 dir2 - copy directories recursively

* mv - move/rename files or directories

* rm - remove files/directories


