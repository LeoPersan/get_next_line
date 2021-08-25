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
# include <unistd.h>
# ifndef t_size
typedef unsigned int	t_size;
# endif

typedef struct s_buffer
{
	int				fd;
	int				length;
	char			*buffer;
	struct s_buffer	*next;
}				t_buffer;

/**
 * @brief Count chars in string
 *
 * @param string	String to be counted
 * @return int		Lenght of string
 */
t_size	ft_strlen(const char *string);

/**
 * @brief Find character in string and return the nomber of the first
 * occurrence position or -1 if not found
 *
 * @param string		Full string
 * @param character		Char to find
 * @return int			Number to first found char or -1 if not found
 */
int		ft_strpos(const char *string, int character);

/**
 * @brief Join two strings in a third string and return the pointer to the
 * third string
 *
 * @param buffer		t_buffer with the first string
 * @param tmp			Second string
 * @param tmp_length	Length of the second string
 * @return char*		Tird string, union of the two original strings
 */
char	*ft_strjoin(t_buffer *buffer, char *tmp, int tmp_length);

/**
 * @brief Duplicate a portion of string and return the pointer this portion
 *
 * @param string	Original string
 * @param start		Position to start copy
 * @param len		Quantity of chars to copy
 * @return char*	Pointer to portion of the original string
 */
char	*ft_substr(char const *string, unsigned int start, t_size len);

/**
 * @brief Remove the first line of the buffer and return the pointer
 * to the first line
 * 
 * @param buffer	t_buffer with string buffer
 * @return char*	Pointer to first line
 */
char	*line_shift(t_buffer *buffer);

/**
 * @brief Return line by line of a file_descriptor
 * 
 * @param file_descriptor   Recurse that point in stream text
 * @return char*            Line of a stream text
 */
char	*get_next_line(int file_descriptor);
#endif
