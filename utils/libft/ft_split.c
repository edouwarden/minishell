/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:46:45 by enormand          #+#    #+#             */
/*   Updated: 2024/11/20 21:57:01 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*dup_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(finish - start + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	ft_gc_free_split(char **split, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		ft_gc_free(split[i]);
		i++;
	}
	ft_gc_free(split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!s || !(split))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = dup_word(s, index, i);
			if (!split[j - 1])
				return (ft_gc_free_split(split, j), NULL);
			index = -1;
		}
		i++;
	}
	return (split[j] = 0, split);
}
