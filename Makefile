NAME = pipex
CFLAGS = -Wall -Werror -Wextra
SRCS = main.c \
	setup.c \
	free_utils.c \
	command_utils.c \
	processes.c \
	split_args.c \
	split_utils.c

all: $(NAME)

$(NAME): $(SRCS)
	$(MAKE) -j -C ./libft add_bonus
	cc $(SRCS) $(CFLAGS) ./libft/libft.a -o $(NAME)

bonus: pipex

clean:
	$(MAKE) -j -C ./libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re

test:
	pipex && cd tests && ./test.sh