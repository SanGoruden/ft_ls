# ft_ls

## overview

This is a project from my school, [42](https://42.fr/en/homepage/). The goal is to recreate ls with the options -a -l -R -r and -t.

For this project I was allowed to use this limited set of functions :
- write
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- listxattr
- getxattr
- time
- ctime
- readlink
- malloc
- free
- perror
- strerror
- exit

Every other function had to be coded from scratch, so I imported 2 of the early 42 projects: ft_printf and libft.

**(these projects were coded following the 42 norm)**

## the program

To compile ft_ls just run

`make`

Then to execute it just run

`./ft_ls [-larRrt] [args]`