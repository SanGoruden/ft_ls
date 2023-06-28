#include "parsing.h"

t_file_list *create_file_list(const char *path, uint8_t flags);

uint8_t set_flags(t_lexer_list *args)
{
    if (!args)
        return 0;

    uint8_t flags = 0;

    while (args && args->type == OPTION)
    {
        int i = 1;
        char option;

        while((option = args->value[i]))
        {
            switch (option)
            {
            case 'R':
                flags |= RECURSIVE;
                break;
            case 'r':
                flags |= REVERSE;
                break;
            case 't':
                flags |= TIME;
                break;
            case 'l':
                flags |= LONGLIST;
                break;
            case 'a':
                flags |= ALL;
                break;
            default:
                break;
            }
            i++;
        }
    args = args->next;
    }
    return flags;
}

int is_directory(char *path)
{
    struct stat file_stats;
    
    if (stat(path, &file_stats) == -1)
    {
        perror(path);
        exit(1);
    }
    return !S_ISREG(file_stats.st_mode);
}

char *get_new_path(const char *path, char *filename)
{
    char *temp;
    char *new_path;

    temp = ft_strjoin(path, "/");
    new_path = ft_strjoin(temp, filename);
    free(temp);


    return new_path;
}

void check_for_directories(t_file_list *file_list, const char *path, uint8_t flags)
{
    char *new_path;

    while (file_list)
    {
        new_path = get_new_path(path, file_list->file->d_name);

        if (is_directory(new_path))
        {
            t_file_list *sub_file_list = create_file_list(new_path, flags);
            if (sub_file_list != NULL)
            {
                check_for_directories(sub_file_list, new_path, flags);
                clear_file_list(&sub_file_list);
            }
        }

        free(new_path);
        file_list = file_list->next;
    }
}

t_file_list *create_file_list(const char *path, uint8_t flags)
{
    DIR *dir;
    struct dirent *dp;

    t_file_list *file_list = NULL;


    if ((dir = opendir(path)) == 0)
    {
        perror(path);
        return NULL;
    }

    while ((dp = readdir(dir)) != 0)
    {
        if (dp->d_name[0] != '.')
            add_file_list(&file_list, dp);
    }

    closedir(dir);
    sort_file_list(file_list, flags);
    print_file_list(file_list, path, flags);
    return file_list;
}

void list_files(t_lexer_list *lexed_args, uint8_t flags)
{
    char *path;

    while (lexed_args && lexed_args->type == OPTION)
        lexed_args = lexed_args->next;
    if (!lexed_args)
    { //TODO: MAKE THIS CLEANER ITS UGLY
        path = ".";
        t_file_list* file_list = create_file_list(path, flags);
        if (flags & RECURSIVE)
            check_for_directories(file_list, path, flags);
        clear_file_list(&file_list);
    }
    while (lexed_args)
    {   
        path = lexed_args->value;         
        t_file_list* file_list = create_file_list(path, flags);
        if (flags & RECURSIVE)
            check_for_directories(file_list, path, flags);
        clear_file_list(&file_list);
        lexed_args = lexed_args->next;
    }
}

int main(int argc, char **argv)
{
    t_lexer_list *lexed_args = create_lexer_list(argc, argv);
    uint8_t flags = set_flags(lexed_args);
    list_files(lexed_args, flags);
    clear_lexer_list(&lexed_args);
    return 0;
}