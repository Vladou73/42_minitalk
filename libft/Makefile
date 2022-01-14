
#VARIABLE=VALUE
CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a

SRCS = ft_atoi.c \
ft_free_null_ptr.c \
ft_memset.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_putchar_fd.c \
ft_strlen.c \

OBJS=$(SRCS:.c=.o)

#*********** RULES ************

%.o : %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#in case files exist with same name as targets
.PHONY: all clean fclean re bonus