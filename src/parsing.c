#include "parsing.h"

int is_option(char *arg)
{
    if (arg[0] != '-')
        return 0;
    for (size_t i = 1; i < ft_strlen(arg); i++)
    {
        if (arg[i] != 'R' 
        && arg[i] != 'l'
        && arg[i] != 'a'
        && arg[i] != 'r'
        && arg[i] != 't')
        {
            printf("%c: illegal option\n", arg[i]);
            exit(1);
        }
    }
    return 1;
}

t_lexer_list *lexer_list_last(t_lexer_list *lexer_list)
{
    if (lexer_list != NULL)
	{
		while (lexer_list->next != NULL)
			lexer_list = lexer_list->next;
	}
	return (lexer_list);
}

t_lexer_list *new_lexer_list(char *arg)
{
    t_lexer_list *new = malloc(sizeof(t_lexer_list));
    if (new == 0)
    {
        perror("malloc");
        exit(1);
    }
    new->value = arg;
    new->type = is_option(arg) ? OPTION : ARG;
    new->next = NULL;
    return new;
}

void add_lexer_list(t_lexer_list **lexer_list, char *arg)
{
    t_lexer_list *new = new_lexer_list(arg);
    if (*lexer_list == NULL)
        *lexer_list = new;
    else
        lexer_list_last(*lexer_list)->next = new;
}

void clear_lexer_list(t_lexer_list **lexer_list)
{
    t_lexer_list *tmp;
    while (*lexer_list)
    {
        tmp = (*lexer_list)->next;
        free(*lexer_list);
        *lexer_list = tmp;
    }
}

t_lexer_list *create_lexer_list(int argc, char **argv)
{
    if (argc < 2)
        return NULL;

    t_lexer_list *lexer_list = NULL;

    for (int i = 1; i < argc; i++)
        add_lexer_list(&lexer_list, argv[i]);

    return lexer_list;
}