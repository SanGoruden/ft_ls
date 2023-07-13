#ifndef LISTING_H
# define LISTING_H

#include "parsing.h"

int         is_directory(char *path);
void        check_for_directories(t_file_list *file_list, const char *path, uint8_t flags);
void        create_and_explore_file_list(char *path, uint8_t flags);
void        list_files(t_lexer_list *lexed_args, uint8_t flags);
t_file_list *create_file_list(const char *path, uint8_t flags);

#endif