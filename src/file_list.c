#include "file_list.h"

t_file_list *new_file_list(struct dirent *file)
{
    t_file_list *new = malloc(sizeof(t_file_list));
    if (new == 0)
    {
        perror("malloc");
        exit(1);
    }
    new->file = file;
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

void add_file_list(t_file_list **file_list, struct dirent *file)
{
    t_file_list *new = new_file_list(file);
    new->next = *file_list;
    *file_list = new;
}

void clear_file_list(t_file_list **file_list)
{
    t_file_list *tmp;
    while (*file_list)
    {
        tmp = (*file_list)->next;
        free(*file_list);
        *file_list = tmp;
    }
}

void print_file_list(t_file_list *file_list, const char *path, uint8_t flags)
{
    if (flags & RECURSIVE)
        printf("\n%s:\n", path);
    while (file_list)
    {
        printf("%s\n", file_list->file->d_name);
        file_list = file_list->next;
    }
}

t_file_list* partition(t_file_list *first, t_file_list *last)
{
    t_file_list*    pivot = first;
    t_file_list*    front = first;
    struct dirent   *temp = 0;

    while (front != NULL && front != last) 
    {
        if (ft_strcmp(front->file->d_name, last->file->d_name) < 0)
        {
            pivot = first;
  
            temp = first->file;
            first->file = front->file;
            front->file = temp;
  
            first = first->next;
        }
  
        front = front->next;
    }
  
    temp = first->file;
    first->file = last->file;
    last->file = temp;
    return pivot;
}

void quick_sort(t_file_list* first, t_file_list* last)
{
    if (first == last)
        return;

    t_file_list* pivot = partition(first, last);
  
    if (pivot != NULL && pivot->next != NULL)
        quick_sort(pivot->next, last);
  
    if (pivot != NULL && first != pivot)
        quick_sort(first, pivot);
}

void sort_file_list(t_file_list *file_list, uint8_t flags)
{
    if (flags & TIME)
        return; //TODO:
    if (flags & REVERSE)
        return; //TODO:

    quick_sort(file_list, file_list_last(file_list));
}
