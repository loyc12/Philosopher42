/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:45:00 by vjean             #+#    #+#             */
/*   Updated: 2022/11/14 12:54:43 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_count_word(char const *s, char limite)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == limite)
			s++;
		if (*s != limite && *s)
			words++;
		while (*s != limite && *s)
			s++;
	}
	return (words);
}

static int	shorten_split(const char *s, char c)
{
	if (ft_strchr(s, c))
		return (ft_strchr(s, c) - s);
	return (ft_strlen(s));
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		len;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	words = ft_count_word(s, c);
	if (words == 0)
		return (NULL);
	tab = ft_calloc(sizeof(char *), (words + 1));
	if (!tab)
		return (NULL);
	while (++i < words)
	{
		while (*s && *s == c)
			s++;
		len = shorten_split(s, c);
		tab[i] = ft_substr(s, 0, len);
		s += len;
	}
	return (tab);
}
