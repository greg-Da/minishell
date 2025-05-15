CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
CFILES = ft_isalpha.c\
	 ft_isdigit.c\
	 ft_isspace.c\
	 ft_isalnum.c\
	 ft_isascii.c\
	 ft_isprint.c\
	 ft_strlen.c\
	 ft_memset.c\
	 ft_bzero.c\
	 ft_memcpy.c\
	 ft_memmove.c\
	 ft_strlcpy.c\
	 ft_strlcat.c\
	 ft_toupper.c\
	 ft_tolower.c\
	 ft_strchr.c\
	 ft_strrchr.c\
	 ft_strncmp.c\
	 ft_strcmp.c\
	 ft_memchr.c\
	 ft_memcmp.c\
	 ft_strnstr.c\
	 ft_atoi.c\
	 ft_calloc.c\
	 ft_strdup.c\
	 ft_substr.c\
	 ft_strjoin.c\
	 ft_strtrim.c\
	 ft_itoa.c\
	 ft_split.c\
	 ft_nsplit.c\
	 ft_strmapi.c\
	 ft_striteri.c\
	 ft_putchar_fd.c\
	 ft_putstr_fd.c\
	 ft_putendl_fd.c\
	 ft_putnbr_fd.c\
	 ft_realloc.c\
	 ft_abs.c\
	 printf/ft_manage.c\
	 printf/ft_printf.c\
	 printf/ft_putchar_fdd.c\
	 printf/ft_putnbr_fdd.c\
	 printf/ft_putstr_fdd.c\
	 get_next_line/get_next_line.c\

BONUS = ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c

OBJS = ${CFILES:.c=.o}

BONUSOBJS = ${BONUS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

bonus: ${BONUSOBJS} ${OBJS}
	ar rcs ${NAME} ${OBJS} ${BONUSOBJS}

fclean:	clean
	rm -rf ${NAME}

clean:
	rm -rf ${OBJS} ${BONUSOBJS}

re:	fclean all

.PHONY: all clean fclean re
