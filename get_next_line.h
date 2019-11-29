/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejuana <ejuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 20:42:57 by ejuana            #+#    #+#             */
/*   Updated: 2019/11/28 22:15:07 by ejuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# define BUFF_SIZE 10000

typedef struct		s_mlist
{
	void			*data;
	size_t			size;
	int				x;
}					t_mlist;

enum				e_strings{glue, duplicate, linebreak};

int					get_next_line(const int fd, char **line);

#endif
