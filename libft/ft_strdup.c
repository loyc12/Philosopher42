/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42quebec.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:54:08 by vajean            #+#    #+#             */
/*   Updated: 2022/05/09 13:03:26 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(char *s1)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (result == NULL)
	{
		return (NULL);
	}
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
