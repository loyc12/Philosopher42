/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42quebec.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 08:21:18 by vjean             #+#    #+#             */
/*   Updated: 2022/09/13 08:04:09 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500

# endif

char	*get_next_line(int fd);
char	*ft_calloc_gnl(size_t count, size_t size);
char	*gnl_str_chr(const char *s1, int c);
size_t	strlen_gnl(const char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(char *s1);

#endif