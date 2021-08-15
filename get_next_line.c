/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoperei <leopso1990@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 21:48:22 by leoperei          #+#    #+#             */
/*   Updated: 2021/08/10 21:48:22 by leoperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_size	ft_strlen(const char *string)
{
	t_size	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

static int	ft_strpos(const char *string, int character)
{
	int	i;

	if (!string)
		return (-1);
	i = -1;
	while (string[++i])
		if (string[i] == (char) character)
			return (i);
	return (-1);
}

char	*ft_strjoin(char *buffer, int *buffer_length, char *tmp, int tmp_length)
{
	t_size	i;
	char	*new_string;

	if (!buffer || !tmp)
		return (NULL);
	i = 0;
	new_string = malloc((*buffer_length + tmp_length + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (*buffer)
		new_string[i++] = *(buffer++);
	while (*tmp)
		new_string[i++] = *(tmp++);
	new_string[i] = 0;
	*buffer_length += tmp_length;
	return (new_string);
}

char	*ft_substr(char const *string, unsigned int start, t_size len)
{
	t_size	i;
	char	*new_string;

	if (!string)
		return (NULL);
	i = ft_strlen(string);
	if (start > i)
		len = 0;
	else if (start + len > i)
		len = i - start;
	new_string = (char *) malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	i = -1;
	while (++i < len)
		new_string[i] = string[start + i];
	new_string[i] = 0;
	return (new_string);
}

static char	*line_shift(char **buffer)
{
	char	*swap;
	char	*line;
	int		new_line;

	new_line = ft_strpos(*buffer, '\n');
	if (new_line < 0)
		return (NULL);
	new_line++;
	line = ft_substr(*buffer, 0, new_line);
	swap = ft_substr(*buffer, new_line, ft_strlen(*buffer) - new_line);
	free(*buffer);
	*buffer = swap;
	return (line);
}

static int	more_buffer(int file_descriptor, char **buffer, int *buffer_length)
{
	char	*tmp;
	char	*swap;
	int		read_result;

	if (ft_strpos(*buffer, '\n') > -1)
		return (1);
	tmp = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	read_result = read(file_descriptor, tmp, BUFFER_SIZE * sizeof(char));
	if (read_result > 0)
	{
		tmp[read_result] = 0;
		swap = ft_strjoin(*buffer, buffer_length, tmp, read_result);
		free(*buffer);
		*buffer = swap;
	}
	free(tmp);
	return (read_result);
}

char	*get_next_line(int file_descriptor)
{
	static int	buffer_length;
	static char	*buffer;
	char		*line;

	if (!buffer)
	{
		buffer = (char *) malloc(sizeof(char));
		buffer[0] = 0;
	}
	while (more_buffer(file_descriptor, &buffer, &buffer_length) > 0)
	{
		line = line_shift(&buffer);
		if (line)
			return (line);
	}
	if (buffer[0])
	{
		line = buffer;
		buffer = NULL;
		return (line);
	}
	return (NULL);
}
