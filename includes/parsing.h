#ifndef PARSING_H
#define PARSING_H

# include "file_list.h"

typedef struct s_lexer_list
{
    int type;
    char *value;
    struct s_lexer_list *next;
}              t_lexer_list;

enum e_type
{
    OPTION,
    ARG
};

int             is_option(char *arg);
t_lexer_list    *new_lexer_list(char *arg);
void            add_lexer_list(t_lexer_list **lexer_list, char *arg);
void            clear_lexer_list(t_lexer_list **lexer_list);
void            print_lexer_list(t_lexer_list *lexer_list);
t_lexer_list    *create_lexer_list(int argc, char **argv);

#endif