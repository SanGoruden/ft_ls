#ifndef FILE_LIST_H
#define FILE_LIST_H

# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/stat.h>
# include <time.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef struct s_file_list
{
    struct dirent		*file;
    const char          *path;
    struct s_file_list	*next;
}				t_file_list;

enum e_flags
{
    RECURSIVE = 1 << 0,
    LONGLIST = 1 << 1,
    ALL = 1 << 2,
    REVERSE = 1 << 3,
    TIME = 1 << 4
};

t_file_list	*new_file_list(struct dirent *file, const char *path);
t_file_list *copy_file_list(t_file_list* file_list);
void		add_file_list(t_file_list **file_list, struct dirent *file, const char *path);
void		clear_file_list(t_file_list **file_list);
void		print_file_list(t_file_list *file_list, const char *path, u_int8_t flags);
void        sort_file_list(t_file_list **file_list, u_int8_t flags);
char        *get_new_path(const char *path, char *filename);



#endif // FILE_LIST_H