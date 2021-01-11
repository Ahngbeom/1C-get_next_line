/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:41:58 by bahn              #+#    #+#             */
/*   Updated: 2021/01/11 14:41:09 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int		extract_line(char **stc_buff, char **line, int lf_idx)
{
	char	*temp;

	*line = ft_substr(*stc_buff, 0, lf_idx);
	if (ft_strlen(*stc_buff) > (lf_idx + 1))
	{
		temp = ft_substr(*stc_buff, (lf_idx + 1), ft_strlen(*stc_buff));
		free(*stc_buff);
		*stc_buff = temp;
		return (1);
	}
	free(*stc_buff);
	*stc_buff = NULL;
	return (1);
}

int		end_of_file(char **stc_buff, char **line, int read_size)
{
	int	lf_idx;

	if (read_size < 0)
		return (-1);
	else if (*stc_buff != NULL && ((lf_idx = find_line_feed(*stc_buff)) >= 0))
		return (extract_line(stc_buff, line, lf_idx));
	else if (*stc_buff != NULL)
	{
		*line = *stc_buff;
		*stc_buff = NULL;
		return (0);
	}
	else
	{
		*line = ft_strdup("");
		return (0);
	}
}

int		get_next_line(int fd, char **line)
{
	static	char	*stc_buff[OPEN_MAX];
	char			buff[BUFFER_SIZE + 1];
	int				read_size;
	int				lf_idx;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((read_size = read(fd, buff, BUFFER_SIZE)))
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
