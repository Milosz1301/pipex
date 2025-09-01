CC=cc
CFLAGS=-Wall -Werror -Wextra -I.
.PHONY: all clean fclean re bonus

SOURCE= ft_split.c ft_strlen.c ft_substr.c ft_strjoin.c ft_strnstr.c
OBJECT= $(SOURCE:.c=.o)

NAME=libft.a

all: $(NAME)

$(NAME): $(OBJECT)
	ar rcs $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^
clean:
	$(RM) $(OBJECT) $(bonusOBJECT)
fclean: clean
	$(RM) $(NAME)
re: fclean all
