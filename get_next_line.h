/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:00:24 by bahn              #+#    #+#             */
/*   Updated: 2021/01/13 00:24:27 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 99
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10
# endif

int			get_next_line(int fd, char **line);

int			ft_strlen(char *str);
char		*ft_strdup(char *src);
size_t		ft_strlcpy(char *dest, char *src, size_t size);
size_t		ft_strlcat(char *dest, char *src, size_t size);
char		*ft_strjoin(char *s1, char *s2);

#endif
