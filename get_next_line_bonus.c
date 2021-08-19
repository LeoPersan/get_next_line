/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoperei <leopso1990@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:49:57 by leoperei          #+#    #+#             */
/*   Updated: 2021/08/14 12:49:57 by leoperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_size ft_strlen(const char *string)
{
	t_size len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

static int ft_strpos(const char *string, int character)
{
	int i;

	if (!string)
		return (-1);
	i = -1;
	while (string[++i])
		if (string[i] == (char)character)
			return (i);
	return (-1);
}

char *ft_strjoin(t_buffer *buffer, char *tmp, int tmp_length)
{
	t_size i;
	char *new_string;

	if (!buffer->buffer || !tmp)
		return (NULL);
	i = -1;
	new_string = malloc((buffer->length + tmp_length + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (buffer->buffer[++i])
		new_string[i] = buffer->buffer[i];
	while (*tmp)
		new_string[i++] = *(tmp++);
	new_string[i] = 0;
	buffer->length += tmp_length;
	return (new_string);
}

char *ft_substr(char const *string, unsigned int start, t_size len)
{
	t_size i;
	char *new_string;

	if (!string)
		return (NULL);
	i = ft_strlen(string);
	if (start > i)
		len = 0;
	else if (start + len > i)
		len = i - start;
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	i = -1;
	while (++i < len)
		new_string[i] = string[start + i];
	new_string[i] = 0;
	return (new_string);
}

static char *line_shift(t_buffer *buffer)
{
	char *swap;
	char *line;
	int new_line;

	new_line = ft_strpos(buffer->buffer, '\n');
	if (new_line < 0)
		return (NULL);
	new_line++;
	line = ft_substr(buffer->buffer, 0, new_line);
	swap = ft_substr(buffer->buffer, new_line, ft_strlen(buffer->buffer) - new_line);
	free(buffer->buffer);
	buffer->buffer = swap;
	return (line);
}

static int more_buffer(t_buffer *buffer)
{
	char *tmp;
	char *swap;
	int read_result;

	if (ft_strpos(buffer->buffer, '\n') > -1)
		return (1);
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	read_result = read(buffer->fd, tmp, BUFFER_SIZE * sizeof(char));
	if (read_result > 0)
	{
		tmp[read_result] = 0;
		swap = ft_strjoin(buffer, tmp, read_result);
		free(buffer->buffer);
		buffer->buffer = swap;
	}
	free(tmp);
	return (read_result);
}

static t_buffer *new_buffer(t_buffer **buffers, int file_descriptor)
{
	*buffers = (t_buffer *)malloc(sizeof(t_buffer));
	(*buffers)->fd = file_descriptor;
	(*buffers)->buffer = (char *)malloc(sizeof(char));
	(*buffers)->buffer[0] = 0;
	(*buffers)->length = 0;
	(*buffers)->next = 0;
	return (*buffers);
}

static t_buffer *get_buffer(t_buffer **buffers, int file_descriptor)
{
	if (!*buffers)
		return (new_buffer(buffers, file_descriptor));
	if ((*buffers)->fd == file_descriptor)
		return (*buffers);
	return (get_buffer(&(*buffers)->next, file_descriptor));
}

static void del_buffer(t_buffer **buffers, t_buffer **buffer)
{
	t_buffer *tmp;

	if ((*buffers)->fd != (*buffer)->fd)
		del_buffer(&(*buffers)->next, buffer);
	else
	{
		tmp = (*buffers)->next;
		free(*buffers);
		*buffers = tmp;
	}
}

char *get_next_line(int file_descriptor)
{
	static t_buffer *buffers;
	t_buffer *buffer;
	char *line;

	buffer = get_buffer(&buffers, file_descriptor);
	while (more_buffer(buffer) > 0)
	{
		line = line_shift(buffer);
		if (line)
			return (line);
	}
	if (buffer->buffer[0])
	{
		line = buffer->buffer;
		del_buffer(&buffers, &buffer);
		return (line);
	}
	return (NULL);
}
