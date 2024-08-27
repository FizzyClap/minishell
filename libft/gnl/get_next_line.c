/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:10:33 by roespici          #+#    #+#             */
/*   Updated: 2024/08/18 14:16:12 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *line, char *buffer)
{
	int		bytes_read;

	bytes_read = 1;
	while (!strchr_gnl(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (strlen_gnl(line) == 0)
				return (free(line), NULL);
			break ;
		}
		buffer[bytes_read] = '\0';
		line = strjoin_gnl(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

static int	find_newline(char *buffer, char *line)
{
	char	*newline_pos;
	char	*temp;

	newline_pos = strchr_gnl(line, '\n');
	if (newline_pos)
	{
		temp = strdup_gnl(newline_pos + 1);
		line[newline_pos - line + 1] = '\0';
		if (!temp)
			return (free(line), 0);
		strcpy_gnl(buffer, temp);
		free(temp);
	}
	else
		buffer[0] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = strdup_gnl("");
	if (!line)
		return (NULL);
	if (buffer[0])
	{
		line = strjoin_gnl(line, buffer);
		if (!line)
			return (NULL);
		buffer[0] = '\0';
	}
	line = read_and_join(fd, line, buffer);
	if (!line)
		return (NULL);
	if (strlen_gnl(line) == 0)
		return (free(line), NULL);
	if (!find_newline(buffer, line))
		return (line);
	return (line);
}
