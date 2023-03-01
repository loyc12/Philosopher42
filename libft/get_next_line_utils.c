/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42quebec.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 09:43:31 by vjean             #+#    #+#             */
/*   Updated: 2022/07/28 15:03:41 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

size_t	strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*newline;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strdup(s2));
	if (!s2)
		return (gnl_strdup(s1));
	newline = malloc((strlen_gnl(s1) + strlen_gnl(s2) + 1) * (sizeof(char)));
	if (!newline)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		newline[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		newline[j++] = s2[i++];
	newline[j] = '\0';
	return (newline);
}

char	*gnl_strdup(char *s1)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc((strlen_gnl(s1) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
