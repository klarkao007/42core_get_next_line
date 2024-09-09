/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_previous_attempts.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbachova <kbachova@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:10:04 by kbachova          #+#    #+#             */
/*   Updated: 2024/09/09 10:10:25 by kbachova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//GNL

// #include "get_next_line.h"

// char	*get_next_line(int fd)
// {
// 	static char	*storing_buffer;
// 	char		*reading_buffer [BUFFER_SIZE + 1];
// 	char		*line_buffer;
// 	int			bytes_read;

// 	storing_buffer = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
// 	line_buffer = NULL;

// 	if (!fd || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	while (bytes_read > 0)
// 	{
// 		bytes_read = 0;
// 		bytes_read = read(fd, reading_buffer, BUFFER_SIZE);
// 		if (bytes_read <= 0)
// 			return (NULL);
// 		reading_buffer[bytes_read] = '\0';
// 		if (find_newline(reading_buffer))
// 		{
// 			line_buffer = before_nl(storing_buffer);
// 			storing_buffer = after_nl(storing_buffer);
// 			return (line_buffer);
// 		}
// 		ft_strjoin(reading_buffer, storing_buffer);
// 	}
// 	return (NULL);
// }

// FUNCTION LOGIC:
// char	*get_next_line(int fd)
//
// 	static char	*storage;
// 	char	*line;
//
// 	while (read(fd, buf, nbytes) > 0)
//
// 	(copies nbytes to buf, moves the "cursor",
//	returns n of bytes read (-1 error, 0 end of file))
//
// 	strjoin buf to storage
//
// 	if storage has \n
// 		copy all from storage up to \n to line
// 		modify storage to only contain chars after \n
// 		return line
//
//	ALTERNATIVE (needs to add copy storage to line first and empty storage)
// 	if line has \n
// 		copy all from line after \n to storage
// 		delete all from line after \n
// 		return line
//
// 	(else = read again)
// 	return NULL

//UTILS

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t				i;
// 	unsigned char		*destination;
// 	const unsigned char	*source;

// 	destination = (unsigned char *)dest;
// 	source = (const unsigned char *)src;
// 	i = 0;
// 	if (!dest && !src)
// 		return (NULL);
// 	while (i < n)
// 	{
// 		destination[i] = source[i];
// 		i++;
// 	}
// 	return (dest);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	len1;
// 	size_t	len2;
// 	char	*new_str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	new_str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	ft_memcpy(new_str, s1, len1);
// 	ft_memcpy(new_str + len1, s2, len2);
// 	new_str[len1 + len2] = '\0';
// 	return (new_str);
// }

//attempt n.2

// {
// 	static char	*storage = NULL;
// 	char		*buf;
// 	int			bytes_read;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	if (storage == NULL)
// 		storage = (char *)malloc(BUFFER_SIZE + 1, sizeof(char));
// 	buf = (char *)malloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (storage == NULL || buf == NULL)
// 	{
// 		free(storage);
// 		free(buf);
// 		return (NULL);
// 	}
// 	bytes_read = read(fd, buf, BUFFER_SIZE);
// 	while (bytes_read > 0)
// 	{
// 		buf[bytes_read] = '\0';
// 		storage = strjoin(storage, buf);
// 		strchr(storage, '\n');
// 	}
// }
