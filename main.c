#include "parsing.h"

void create_file_list(const char *path, uint8_t flags);


uint8_t set_flags(t_lexer_list **args)
{
    uint8_t flags = 0;

    while (*args)
    {
        if ((*args)->type == OPTION)
        {
            int i = 1;
            char option;

            while((option = (*args)->value[i]))
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
        }
        *args = (*args)->next;
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

    t_file_list *temp = file_list;

    while (file_list)
    {
        new_path = get_new_path(path, file_list->file->d_name);

        printf("NEW:  PATH: %s FILENAME: %s\n", path, file_list->file->d_name);
        print_file_list(temp, path, flags);
        printf("======================================================================\n");

        if (is_directory(new_path))
        {
            // printf("NEW_PATH: %s\n", new_path);
            create_file_list(new_path, flags);
        }
        free(new_path);
        file_list = file_list->next;
        if (file_list == NULL)
            printf("RATIO\n");
        temp = file_list;
    }
    printf("RATIO2\n");
}

void create_file_list(const char *path, uint8_t flags)
{
    DIR *dir;
    struct dirent *dp;

    t_file_list *file_list = NULL;


    if ((dir = opendir(path)) == 0)
    {
        perror(path);
        return ;
    }

    while ((dp = readdir(dir)) != 0)
    {
        if (dp->d_name[0] != '.')
        {
            // printf("FILENAME: %s\n", dp->d_name);
            add_file_list(&file_list, dp);
        }
    }

    closedir(dir);
    sort_file_list(file_list, flags);
    // print_file_list(file_list, path, flags);
    if (flags & RECURSIVE)
    {
        printf("\nNEWFILELISTTTTTTTTTTTT\n");
        check_for_directories(file_list, path, flags);
    }
    clear_file_list(&file_list);
}

int main(int argc, char **argv)
{
    t_lexer_list *lexed_args = create_lexer_list(argc, argv);
    uint8_t flags = set_flags(&lexed_args);
    create_file_list(".", flags);
    return 0;
}