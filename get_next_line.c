/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbachova <kbachova@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:19:49 by kbachova          #+#    #+#             */
/*   Updated: 2024/09/13 16:27:36 by kbachova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		subs = (char *)malloc(1);
		if (!subs)
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	if ((len + start) > s_len)
		len = s_len - start;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	ft_memcpy(subs, s + start, len);
	subs[len] = '\0';
	return (subs);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	return (new_str);
}

char	*fill_line_buf(int fd, char *storage, char *buf)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(storage);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (storage == NULL)
			storage = ft_strdup("");
		temp = storage;
		storage = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

char	*set_line(char *line_buf)
{
	char	*storage;
	char	*nl_ptr;
	size_t	nl_index;

	if (!line_buf)
		return (NULL);
	nl_ptr = ft_strchr(line_buf, '\n');
	if (nl_ptr)
		nl_index = nl_ptr - line_buf;
	else
		nl_index = ft_strlen(line_buf);
	storage = ft_substr(line_buf, 0, nl_index);
	if (*storage == '\0')
	{
		free(storage);
		storage = NULL;
	}
	line_buf[nl_index] = '\0';
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*next_line;
	char		*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(storage);
		free(buf);
		storage = NULL;
		buf = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	next_line = fill_line_buf(fd, storage, buf);
	free(buf);
	buf = NULL;
	if (!next_line)
		return (NULL);
	storage = set_line(next_line);
	return (next_line);
}
