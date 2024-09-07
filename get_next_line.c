/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbachova <kbachova@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:19:49 by kbachova          #+#    #+#             */
/*   Updated: 2024/09/07 17:53:45 by kbachova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*buf;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (storage == NULL)
		storage = (char *)malloc(BUFFER_SIZE + 1, sizeof(char));
	buf = (char *)malloc(BUFFER_SIZE + 1, sizeof(char));
	if (storage == NULL || buf == NULL)
	{
		free(storage);
		free(buf);
		return (NULL);
	}
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		storage = strjoin(storage, buf);
		strchr(storage, '\n');
	}
}
