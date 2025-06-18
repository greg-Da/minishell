/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:09:04 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/18 11:31:11 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_abs(int nb);
char				**ft_nsplit(char const *s, char c, size_t limit);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *str);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memswap(void *p1, void *p2, size_t size);
int					ft_memcmp(void *pnt1, void *pnt2, int size);
int					ft_strlen(char *str);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
int					ft_lstsize(t_list *lst);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				*ft_bzero(void *pnt, size_t count);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void				*ft_calloc(int count, size_t size);
void				*ft_memchr(void *pnt, int chr, int size);
void				*ft_memcpy(void *dest, const void *src, int size);
void				*ft_memmove(void *dest, void *src, int size);
void				*ft_memset(void *pnt, int val, int count);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(char *src);
char				*ft_strrchr(char *str, int c);
char				*ft_strnstr(char *str, char *to_find, int len);
char				*ft_strchr(char *str, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
unsigned int		ft_strlcat(char *dest, char *src, unsigned int nb);
unsigned int		ft_strlcpy(char *dest, char *src, unsigned int n);
int					ft_is_space(char c);

int					ft_include(char c, const char *set);
#endif