NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra 

SRCS = 	pipex.c\
	libft/libft.a

BIN = pipex.o 

$(NAME) : $(BIN)
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(BIN)

re : fclean all
