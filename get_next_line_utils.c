/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:30:04 by hhk               #+#    #+#             */
/*   Updated: 2021/01/06 14:06:05 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;
	size_t		j;
	size_t		slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	i = start;
	j = 0;
	if (!(sub = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < slen && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}

size_t			ft_strlen(const char *str)
{
	size_t		idx;

	idx = 0;
	while (str[idx] != '\0')
		idx++;
	return (idx);
}

char			*ft_strdup(const char *s1)
{
	char		*dest;
	int			len;
	int			idx;

	len = ft_strlen(s1);
	if (!(dest = (char *)malloc(len + 1)))
		return (0);
	idx = 0;
	while (s1[idx] != '\0')
	{
		dest[idx] = s1[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}

char			*ft_strjoin(char *s1, char *s2)
{
	char		*temp;
	int			totalsize;
	int			idx;
	int			i;

	if (!s1 && !s2)
		return (0);
	totalsize = 0;
	idx = 0;
	i = 0;
	totalsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(temp = (char *)malloc(sizeof(char) * totalsize)))
		return (0);
	while (s1[idx] != '\0')
	{
		temp[idx] = s1[idx];
		idx++;
	}
	while (s2[i] != '\0')
		temp[idx++] = s2[i++];
	temp[totalsize - 1] = '\0';
	free(s1);
	return (temp);
}
