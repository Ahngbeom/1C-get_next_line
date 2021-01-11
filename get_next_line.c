/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:41:58 by bahn              #+#    #+#             */
/*   Updated: 2021/01/11 21:13:08 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t  i;
	char    *ptr;

	i = 0;
	if ((size_t)ft_strlen((char *)s) < start)
	{
		if (!(ptr = malloc(1)))
			return (NULL);
		ptr[i] = '\0';
	}
	else
	{
		if (!(ptr = malloc(len + 1)))
			return (NULL);
		while (i < len && s[start] != '\0')
			ptr[i++] = s[start++];
		ptr[i] = '\0';
	}
	return (ptr);
}

int		find_line_feed(char *stc_buff)
{
	int	i;

	i = 0;
	while (stc_buff[i] != '\0')
	{
		if (stc_buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}


//#include <stdio.h>
int		extract_line(char **stc_buff, char **line, int lf_idx)
{
	char	*temp;

	*line = ft_substr(*stc_buff, 0, lf_idx);
	if (ft_strlen(*stc_buff) > (lf_idx + 1))
	{
		temp = ft_substr(*stc_buff, (lf_idx + 1), ft_strlen(*stc_buff));
		free(*stc_buff);
		//printf("stc_buff FREE!!!, stc_buff = temp\n");
		*stc_buff = temp;
		return (1);
	}
	free(*stc_buff);
	//printf("stc_buff FREE!!!, stc_buff = NULL\n");
	*stc_buff = NULL;
	return (1);
}

int		end_of_file(char **stc_buff, char **line, int read_size)
{
	int	lf_idx;

	if (read_size < 0)
		return (-1);
	if (*stc_buff != NULL && ((lf_idx = find_line_feed(*stc_buff)) >= 0))
		return (extract_line(stc_buff, line, lf_idx));
	else if (*stc_buff != NULL)
	{
		*line = *stc_buff;
		*stc_buff = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static	char	*stc_buff[OPEN_MAX];
	char			buff[BUFFER_SIZE + 1];
	ssize_t				read_size;
	ssize_t				lf_idx;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (-1);
	while ((read_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_size] = '\0';
		if (!stc_buff[fd])
			stc_buff[fd] = ft_strdup(buff);
		else
			stc_buff[fd] = ft_strjoin(stc_buff[fd], buff);
		if ((lf_idx = find_line_feed(stc_buff[fd])) >= 0)
			return (extract_line(&stc_buff[fd], line, lf_idx));
	}
	return (end_of_file(&stc_buff[fd], line, read_size));
}
