CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libftprintf.a
CFILES = ft_printf.c \
		ft_manage.c \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \

OBJS = ${CFILES:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

fclean:	clean
	rm -rf ${NAME}

clean:
	rm -rf ${OBJS}

re:	fclean all

.PHONY: all clean fclean re