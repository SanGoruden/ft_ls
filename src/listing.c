#include "listing.h"

int is_directory(char *path)
{
    struct stat file_stats;
    
    if (lstat(path, &file_stats) == -1)
    {
        perror(path);
        exit(1);
    }
    return S_ISDIR(file_stats.st_mode);
}

void check_for_directories(t_file_list *file_list, const char *path, uint8_t flags)
{
    char *new_path;

    while (file_list)
    {
        if (!ft_strcmp(file_list->file->d_name, ".") || !ft_strcmp(file_list->file->d_name, ".."))
        {
            file_list = file_list->next;
            continue;
        }

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
        if (flags & ALL || dp->d_name[0] != '.')
            add_file_list(&file_list, dp, get_new_path(path, dp->d_name));
    }

    closedir(dir);
    sort_file_list(&file_list, flags);
    print_file_list(file_list, path, flags);
    return file_list;
}

void create_and_explore_file_list(char *path, uint8_t flags)
{
    t_file_list* file_list = create_file_list(path, flags);
    if (flags & RECURSIVE)
        check_for_directories(file_list, path, flags);
    clear_file_list(&file_list);
}

void list_files(t_lexer_list *lexed_args, uint8_t flags)
{
    char *path;

    while (lexed_args && lexed_args->type == OPTION)
        lexed_args = lexed_args->next;
    if (!lexed_args)
        create_and_explore_file_list(".", flags);
    while (lexed_args)
    {   
        path = lexed_args->value;         
        create_and_explore_file_list(path, flags);
        lexed_args = lexed_args->next;
    }
}