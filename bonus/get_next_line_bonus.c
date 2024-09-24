/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_buf_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbachova <kbachova@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:06:17 by kbachova          #+#    #+#             */
/*   Updated: 2024/09/17 12:07:52 by kbachova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strjoin(char *s1, char *s2)
{
	char			*smn;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	smn = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!smn)
		return (NULL);
	while (s1[j])
		smn[i++] = s1[j++];
	j = 0;
	while (s2[j])
		smn[i++] = s2[j++];
	smn[i] = '\0';
	return (smn);
}

static char	*fill_line_buf(int fd, char *storage, char *buf)
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
		if (!storage)
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

static char	*set_line(char *line)
{
	char	*storage;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	storage = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*storage == '\0' || storage == NULL)
	{
		free(storage);
		storage = NULL;
	}
	line[i + 1] = '\0';
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;
	char		*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		free(buf);
		buf = NULL;
		return (NULL);
	}
	if (!buff)
		return (NULL);
	line = fill_line_buf(fd, storage[fd], buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	storage[fd] = set_line(line);
	return (line);
}

// //TEST WITH FILE test.txt
//
// int	main(void)
// {
// 	int		fd;
// 	char	*r_line;
//
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		write(1, "ERROR, FILE NOT FOUND!\n", 23);
// 		return (0);
// 	}
// 	r_line = get_next_line(fd);
// 	printf("%s", get_next_line(fd));
// 	if (r_line != NULL)
// 		free(r_line);
// 	r_line = get_next_line(fd);
// 	printf("%s", get_next_line(fd));
// 	if (r_line != NULL)
// 		free(r_line);
// 	r_line = get_next_line(fd);
// 	printf("%s", get_next_line(fd));
// 	if (r_line != NULL)
// 		free(r_line);
// 	return (0);
// }
//
//
// //TEST FOR STANDARD INPUT
//
// int	main(void)
// {
// 	char	*r_line;
//
// 	r_line = get_next_line(1);
// 	printf("%s", r_line);
// 	if (r_line != NULL)
// 		free(r_line);
// 	r_line = get_next_line(1);
// 	printf("%s", r_line);
// 	if (r_line != NULL)
// 		free(r_line);
// 	return (0);
// }