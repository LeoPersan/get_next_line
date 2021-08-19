/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoperei <leopso1990@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 22:17:28 by leoperei          #+#    #+#             */
/*   Updated: 2021/08/10 22:17:28 by leoperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef t_size
typedef unsigned int	t_size;
# endif

typedef struct	s_buffer
{
	int				fd;
	int 			length;
	char			*buffer;
	struct s_buffer	*next;
}				t_buffer;

/**
 * @brief Return line by line of a file_descriptor
 * 
 * @param file_descriptor   recurse that point in stream text
 * @return char*            line of a stream text
 */
char	*get_next_line(int file_descriptor);
#endif
