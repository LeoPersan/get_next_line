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

#include "get_next_line_bonus.h"

static int	more_buffer(t_buffer *buffer)
{
	char	*tmp;
	char	*swap;
	int		read_result;

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

static t_buffer	*new_buffer(t_buffer **buffers, int file_descriptor)
{
	*buffers = (t_buffer *)malloc(sizeof(t_buffer));
	(*buffers)->fd = file_descriptor;
	(*buffers)->buffer = (char *)malloc(sizeof(char));
	(*buffers)->buffer[0] = 0;
	(*buffers)->length = 0;
	(*buffers)->next = 0;
	return (*buffers);
}

static t_buffer	*get_buffer(t_buffer **buffers, int file_descriptor)
{
	if (!*buffers)
		return (new_buffer(buffers, file_descriptor));
	if ((*buffers)->fd == file_descriptor)
		return (*buffers);
	return (get_buffer(&(*buffers)->next, file_descriptor));
}

static void	del_buffer(t_buffer **buffers, t_buffer **buffer)
{
	t_buffer	*tmp;

	if ((*buffers)->fd != (*buffer)->fd)
		del_buffer(&(*buffers)->next, buffer);
	else
	{
		tmp = (*buffers)->next;
		free(*buffers);
		*buffers = tmp;
	}
}

char	*get_next_line(int file_descriptor)
{
	static t_buffer	*buffers;
	t_buffer		*buffer;
	char			*line;

	buffer = get_buffer(&buffers, file_descriptor);
	while (more_buffer(buffer) > 0)
	{
		line = line_shift(buffer);
		if (line)
			return (line);
	}
	line = NULL;
	if (buffer->buffer[0])
		line = buffer->buffer;
	else
		free(buffer->buffer);
	del_buffer(&buffers, &buffer);
	return (line);
}
