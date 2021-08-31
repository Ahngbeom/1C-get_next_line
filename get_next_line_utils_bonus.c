/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:29:41 by bahn              #+#    #+#             */
/*   Updated: 2021/08/31 17:18:23 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*(str++) != '\0')
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	src_length;

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

char	*ft_strdup(char *src)
{
	int		i;
	int		src_len;
	char	*cpy;

	i = 0;
	src_len = ft_strlen(src);
	cpy = (char *)malloc(sizeof(char) * src_len + 1);
	if (!cpy)
		return (NULL);
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
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
	free(s1);
	return (ptr);
}
