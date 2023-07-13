NAME	=	ft_ls

SRCS	=	main.c \
			src/file_list.c \
			src/parsing.c \
			src/printing.c \
			src/listing.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -Iincludes/

LIB		=	-L. -lft

RM		=	rm -f

.c.o :
		@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all	:
		@$(MAKE) -C ./libft
		@mv ./libft/libft.a .
		@make $(NAME)

$(NAME)	:	$(OBJS)
			@$(CC) -o $(NAME) $(OBJS) $(LIB)

debug	:	$(OBJS)
			@$(MAKE) -C ./libft
			@mv ./libft/libft.a .
			gcc -o $(NAME) $(OBJS) $(LIB) -g3

clean	:
		@$(MAKE) clean -C ./libft
		@$(RM) $(OBJS)

fclean	:	clean
		@$(MAKE) fclean -C ./libft
		@$(RM) $(NAME) libft.a

re	:	fclean all

.PHONY:	all clean fclean re
