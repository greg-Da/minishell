/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:58:09 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/13 20:16:51 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static int	ft_chrinstr(int c, const char *s)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if ((int)s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	calc_mal(char const *s1, char const *set)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (ft_chrinstr(s1[i], set) == 1 && s1[i])
	{
		i++;
		result++;
	}
	if (!s1[i])
		return (result);
	i = ft_strlen(s1) - 1;
	while (ft_chrinstr(s1[i], set) == 1 && i >= 0 && s1[i])
	{
		i--;
		result++;
	}
	return (result);
}

static int	check(char const *set)
{
	if (set)
		return (0);
	return (1);
}

static char	*return_error(char const *s1)
{
	char	*result;

	result = malloc(ft_strlen(s1) + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	result[ft_strlen(s1)] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		u;
	int		size;
	char	*result;

	if (!s1)
		return (NULL);
	if (check(set) == 1)
		return (return_error(s1));
	i = 0;
	u = 0;
	size = (ft_strlen(s1) - calc_mal(s1, set)) + 1;
	result = malloc(size);
	while (ft_chrinstr(s1[i], set) == 1 && s1[i])
		i++;
	while (u < size - 1)
	{
		result[u] = s1[i];
		i++;
		u++;
	}
	result[u] = '\0';
	return (result);
}
// int main()
// {
// 	char *test = NULL;
// 	char *rmv = " 	";
// 	char *nvtest = ft_strtrim(test, rmv);
// 	printf("%s\n", nvtest);
// 	free(nvtest);
// }
