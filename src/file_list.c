#include "file_list.h"

char *get_new_path(const char *path, char *filename)
{
    char *temp;
    char *new_path;

    temp = ft_strjoin(path, "/");
    new_path = ft_strjoin(temp, filename);
    free(temp);

    return new_path;
}

t_file_list *new_file_list(struct dirent *file, const char *path)
{
    t_file_list *new = malloc(sizeof(t_file_list));
    if (new == NULL)
    {
        perror("malloc");
        exit(1);
    }
    new->file = malloc(sizeof(struct dirent));
    if (new->file == NULL)
    {
        perror("malloc");
        free(new);
        exit(1);
    }

    memcpy(new->file, file, sizeof(struct dirent));
    new->path = path;
    new->next = NULL;
    return new;
}

t_file_list *file_list_last(t_file_list *file_list)
{
    if (file_list != NULL)
	{
		while (file_list->next != NULL)
			file_list = file_list->next;
	}
	return (file_list);
}

void add_file_list(t_file_list **file_list, struct dirent *file, const char *path)
{
    t_file_list *new = new_file_list(file, path);
    new->next = *file_list;
    *file_list = new;
}

void clear_file_list(t_file_list **file_list)
{
    t_file_list *tmp;
    while (*file_list)
    {
        tmp = (*file_list)->next;
        free((*file_list)->file);
        free((char *)(*file_list)->path);
        free(*file_list);
        *file_list = tmp;
    }
}

void print_file_stats(t_file_list *file)
{
    struct stat file_stats;
    char test[11] = "----------";

    if (lstat(file->path, &file_stats) == -1)
    {
        perror("stat");
        exit(1);
    }

    //TODO: this is just for testing how st_mode works
    mode_t file_mode = file_stats.st_mode;
    test[1] = file_mode & S_IRUSR ? 'r' : '-';
    test[2] = file_mode & S_IWUSR ? 'w' : '-';
    test[3] = file_mode & S_IXUSR ? 'x' : '-';
    test[4] = file_mode & S_IRGRP ? 'r' : '-';
    test[5] = file_mode & S_IWGRP ? 'w' : '-';
    test[6] = file_mode & S_IXGRP ? 'x' : '-';
    test[7] = file_mode & S_IROTH ? 'r' : '-';
    test[8] = file_mode & S_IWOTH ? 'w' : '-';
    test[9] = file_mode & S_IXOTH ? 'x' : '-';

    printf("%s ", test);
    return ;
}

void print_file_list(t_file_list *file_list, const char *path, uint8_t flags)
{
    if (flags & RECURSIVE)
        printf("\n%s:\n", path);
    while (file_list)
    {
        if (flags & LONGLIST)
            print_file_stats(file_list);
        printf("%s\n", file_list->file->d_name);
        file_list = file_list->next;
    }
}

int compare_files(t_file_list *file1, t_file_list *file2, uint8_t flags)
{
    if (flags & TIME)
    {
        struct stat file1_stats;
        struct stat file2_stats;

        if (lstat(file1->path, &file1_stats) == -1 || lstat(file2->path, &file2_stats) == -1)
        {
            perror("stat");
            exit(1);
        }
        return file1_stats.st_mtime < file2_stats.st_mtime ? 1 : -1;
    }
    else
        return ft_strcmp(file1->file->d_name, file2->file->d_name);
}

t_file_list* partition(t_file_list *first, t_file_list *last, uint8_t flags)
{
    t_file_list*    pivot = first;
    t_file_list*    front = first;
    struct dirent   *temp = 0;
    const char      *temp_path = 0;

    while (front != NULL && front != last) 
    {
        if (compare_files(front, last, flags) < 0)
        {
            pivot = first;
  
            temp = first->file;
            temp_path = first->path;
            first->file = front->file;
            first->path = front->path;
            front->file = temp;
            front->path = temp_path;
  
            first = first->next;
        }
  
        front = front->next;
    }
  
    temp = first->file;
    temp_path = first->path;
    first->file = last->file;
    first->path = last->path;
    last->file = temp;
    last->path = temp_path;
    return pivot;
}

void quick_sort(t_file_list* first, t_file_list* last, uint8_t flags)
{
    if (first == last)
        return;

    t_file_list* pivot = partition(first, last, flags);
  
    if (pivot != NULL && pivot->next != NULL)
        quick_sort(pivot->next, last, flags);
  
    if (pivot != NULL && first != pivot)
        quick_sort(first, pivot, flags);
}

void reverse_file_list(t_file_list **file_list)
{
    t_file_list *current = *file_list;
    t_file_list *prev = NULL;
    t_file_list *next = NULL;

    while (current != NULL) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *file_list = prev;
}

void sort_file_list(t_file_list **file_list, uint8_t flags)
{
    quick_sort(*file_list, file_list_last(*file_list), flags);

    if (flags & REVERSE)
        reverse_file_list(file_list);
}
