/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:29:41 by bahn              #+#    #+#             */
/*   Updated: 2021/01/11 14:42:44 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int count;

	count = 0;
	while (*(str++) != '\0')
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t i;
	size_t src_length;

	i = 0;
	src_length = (size_t)ft_strlen(src);
	if (size == 0)
		return (src_length);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_length);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;

	i = 0;
	j = 0;
	dest_len = (size_t)ft_strlen(dest);
	if (dest_len > size)
		return (ft_strlen(src) + size);
	while (dest[i] != '\0')
		i++;
	while (j + dest_len + 1 < size && src[j] != '\0')
	{
		dest[i] = src[j++];
		i++;
	}
	dest[i] = '\0';
	return (dest_len + ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

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

char	*ft_strdup(char *src)
{
	int		i;
	int		src_len;
	char	*cpy;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	cpy = malloc(sizeof(char) * src_len + 1);
	if (!cpy)
		return (NULL);
	while (i < src_len)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	ptr = malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, (char *)s1, s1_len + 1);
	ft_strlcat(ptr, (char *)s2, s1_len + s2_len + 1);
	return (ptr);
}
