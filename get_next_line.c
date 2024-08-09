/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbachova <kbachova@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:19:49 by kbachova          #+#    #+#             */
/*   Updated: 2024/08/09 15:45:47 by kbachova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storing_buffer;
	char		*reading_buffer [BUFFER_SIZE + 1];
	char		*line_buffer;
	int			bytes_read;

	storing_buffer = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	line_buffer = NULL;

	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = 0;
		bytes_read = read(fd, reading_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		reading_buffer[bytes_read] = '\0';
		if (find_newline(reading_buffer))
		{
			line_buffer = before_nl(storing_buffer);
			storing_buffer = after_nl(storing_buffer);
			return (line_buffer);
		}
		ft_strjoin(reading_buffer, storing_buffer);
	}
	return (NULL);
}
