/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:36:13 by bahn              #+#    #+#             */
/*   Updated: 2021/01/13 00:45:53 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9999
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 100
# endif

int			get_next_line(int fd, char **line);

int			ft_strlen(char *str);
char		*ft_strdup(char *src);
size_t		ft_strlcpy(char *dest, char *src, size_t size);
size_t		ft_strlcat(char *dest, char *src, size_t size);
char		*ft_strjoin(char *s1, char *s2);

#endif
