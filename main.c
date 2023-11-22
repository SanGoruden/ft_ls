#include "parsing.h"
#include "printing.h"
#include "listing.h"

u_int8_t set_flags(t_lexer_list *args)
{
    if (!args)
        return 0;

    u_int8_t flags = 0;

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

int main(int argc, char **argv)
{
    t_lexer_list *lexed_args = create_lexer_list(argc, argv);
    u_int8_t flags = set_flags(lexed_args);
    list_files(lexed_args, flags);
    clear_lexer_list(&lexed_args);
    return 0;
}