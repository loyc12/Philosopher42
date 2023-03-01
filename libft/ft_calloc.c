/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:52:15 by vjean             #+#    #+#             */
/*   Updated: 2023/01/26 14:55:36 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_recalloc(void *ptr, size_t new_count, size_t count, size_t size)
{
	void	*new_ptr;

	if (new_count)
	{
		if (new_count == count)
			return (ptr);
		new_ptr = ft_calloc(new_count, size);
		if (!ptr)
			return (new_ptr);
		if (new_count < count)
			ft_memcpy(new_ptr, ptr, new_count * size);
		else
			ft_memcpy(new_ptr, ptr, count * size);
		ft_free_null(ptr);
		return (new_ptr);
	}
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
