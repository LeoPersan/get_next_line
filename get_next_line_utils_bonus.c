/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoperei <leopso1990@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:50:06 by leoperei          #+#    #+#             */
/*   Updated: 2021/08/14 12:50:06 by leoperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_size	ft_strlen(const char *string)
{
	t_size	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

int	ft_strpos(const char *string, int character)
{
	int	i;

	if (!string)
		return (-1);
	i = -1;
	while (string[++i])
		if (string[i] == (char)character)
			return (i);
	return (-1);
}

char	*ft_strjoin(t_buffer *buffer, char *tmp, int tmp_length)
{
	t_size	i;
	char	*new_string;

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
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	i = -1;
	while (++i < len)
		new_string[i] = string[start + i];
	new_string[i] = 0;
	return (new_string);
}

char	*line_shift(t_buffer *buffer)
{
	char	*swap;
	char	*line;
	int		new_line;

	new_line = ft_strpos(buffer->buffer, '\n');
	if (new_line < 0)
		return (NULL);
	new_line++;
	line = ft_substr(buffer->buffer, 0, new_line);
	swap = ft_substr(buffer->buffer, new_line, buffer->length - new_line);
	free(buffer->buffer);
	buffer->buffer = swap;
	buffer->length -= new_line;
	return (line);
}
