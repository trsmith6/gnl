/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trsmith <trsmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:40:44 by trsmith           #+#    #+#             */
/*   Updated: 2024/04/12 09:54:35 by trsmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(data);
		free(buffer);
		data = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	data = data_filling(fd, data, buffer);
	if (*data == 0)
	{
		free (data);
		return (data = 0);
	}
	line = extract_line(data, line);
	data = extract_new_data(data);
	return (line);
}

char	*data_filling(int fd, char *data, char *buffer)
{
	ssize_t	memsize;

	memsize = 1;
	if (!data)
		data = ft_strdup("");
	while (memsize > 0)
	{
		memsize = read(fd, buffer, BUFFER_SIZE);
		if (memsize == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[memsize] = 0;
		data = ft_strjoin (data, buffer);
		if ((ft_strchr(buffer, '\n')))
			break ;
	}
	free (buffer);
	return (data);
}

char	*extract_new_data(char	*data)
{
	int		len;
	int		i;
	char	*new_data;

	len = 0;
	i = 0;
	if (data == NULL)
		return (NULL);
	while (data[len] != '\n' && data[len])
		len++;
	if (data[len] == '\n')
		len++;
	new_data = malloc((ft_strlen(data) - len + 1) * sizeof(char));
	if (!new_data)
		return (NULL);
	while (data[len + i])
	{
		new_data[i] = data[len + i];
		i++;
	}
	free (data);
	new_data[i] = 0;
	return (new_data);
}

char	*extract_line(char *data, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (data == NULL)
		return (NULL);
	while (data[len] != '\n' && data[len])
		len++;
	if (data[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = data[i];
		i++;
	}
	line[i] = 0;
	return (line);
}
