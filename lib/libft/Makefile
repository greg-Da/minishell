FLAGS=-Wall -Wextra -Werror
FILES=	ft_isalpha.c\
		ft_memcmp.c\
		ft_strdup.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_isascii.c\
		ft_memcpy.c\
		ft_strlcat.c\
		ft_strrchr.c\
		ft_bzero.c\
		ft_isdigit.c\
		ft_memmove.c\
		ft_memswap.c\
		ft_strlcpy.c\
		ft_tolower.c\
		ft_calloc.c\
		ft_isprint.c\
		ft_memset.c\
		ft_strlen.c\
		ft_toupper.c\
		ft_isalnum.c\
		ft_memchr.c\
		ft_strchr.c\
		ft_strncmp.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_realloc.c\
		ft_strcmp.c\
		ft_nsplit.c\
		ft_strtrim.c\
		ft_abs.c
FILES_BONUS=	ft_lstnew_bonus.c\
				ft_lstsize_bonus.c\
				ft_lstlast_bonus.c\
				ft_lstadd_back_bonus.c\
				ft_lstdelone_bonus.c\
				ft_lstclear_bonus.c\
				ft_lstiter_bonus.c\
				ft_lstmap_bonus.c\
				ft_lstadd_front_bonus.c
OBJS=$(FILES:.c=.o)
OBJS_BONUS=$(FILES_BONUS:.c=.o)
NAME=libft.a

all: $(NAME)

bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c
	cc $(FLAGS) -I includes -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
