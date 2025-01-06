/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:02 by luide-ca          #+#    #+#             */
/*   Updated: 2024/12/17 11:04:05 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_count_items(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*ptr_src;
	char		*ptr_dst;
	size_t		i_total_len;

	ptr_src = src;
	ptr_dst = dst;
	i_total_len = 0;
	while (*ptr_src)
	{
		ptr_src++;
		i_total_len++;
	}
	if (size == 0)
		return (i_total_len);
	while ((size - 1 > 0) && *src)
	{
		*ptr_dst = *src;
		ptr_dst++;
		src++;
		size--;
	}
	*ptr_dst = '\0';
	return (i_total_len);
}

static char	*ft_allocate_word(const char *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**ft_free_split(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	result = malloc((ft_count_items(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = ft_allocate_word(s, c);
			if (!result[i])
				return (ft_free_split(result, i));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
