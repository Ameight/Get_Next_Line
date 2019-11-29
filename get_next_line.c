/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejuana <ejuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 20:42:52 by ejuana            #+#    #+#             */
/*   Updated: 2019/11/29 01:53:04 by ejuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/includes/libft.h"

static t_list			*get_file(int fd, t_list **head)
{
	t_list			*file;
	t_mlist			fd_lst;

	fd_lst.x = fd;
	fd_lst.data = NULL;
	fd_lst.size = 0;
	if ((file = *head))
	{
		while (file)
		{
			if (((t_mlist *)file->content)->x == fd)
				return (file);
			file = file->next;
		}
	}
	if (!(file = ft_lstnew(&fd_lst, sizeof(fd_lst))))
		return (0);
	if (!(*head))
		*head = file;
	else
		ft_lstadd(head, file);
	return (file);
}

static int				reader(t_mlist **lst, char **line, const int fd)
{
	int		len;
	char	*str[3];
	char	buf[BUFF_SIZE + 1];

	while ((len = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[len] = 0;
		if (!(str[linebreak] = ft_strchr_safe(buf, '\n')))
			str[glue] = ft_strjoin(*line, buf);
		else
		{
			*str[linebreak] = 0;
			(*lst)->size = ft_strlen(str[linebreak] + 1) + 1;
			if (!(str[glue] = ft_strjoin(*line, buf)) ||\
			!(str[duplicate] = ft_strdup_safe(str[linebreak] + 1)))
				return (-1);
			(*lst)->data = str[duplicate];
		}
		ft_memdel((void **)line);
		if (!(*line = str[glue]))
			return (-1);
		if (str[linebreak])
			break ;
	}
	return (len);
}

static int				get_cache(t_mlist **lst, char **line)
{
	size_t		len;
	char		*curr;
	char		*temp;

	if (!(curr = ft_strchr_safe((*lst)->data, '\n')))
		len = (*lst)->size + 1;
	else
		len = (curr + 1) - (char *)(*lst)->data;
	if ((*line = (char *)ft_realloc(*line, len)) == (char *)0)
		return (-1);
	ft_memcpy(*line, (*lst)->data, len - 1);
	(*line)[len - 1] = 0;
	if (curr)
	{
		(*lst)->size -= len;
		temp = (char *)ft_strdup_safe((*lst)->data + len);
		ft_memdel((void **)&((*lst)->data));
		(*lst)->data = temp;
		return (0);
	}
	ft_memdel((void **)&((*lst)->data));
	(*lst)->size = 0;
	return (1);
}

int						get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*file;
	t_mlist			*lst;
	int				flag1;
	int				flag2;

	if (fd < 0 || !line || read(fd, 0, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	*line = ft_strnew(0);
	flag1 = 1;
	flag2 = 0;
	if (!(file = get_file(fd, &head)))
		return (-1);
	lst = file->content;
	if (lst->size)
		flag1 = get_cache(&lst, line);
	if (flag1)
		flag2 = reader(&lst, line, fd);
	if (flag2 < 0)
		return (-1);
	if (!(lst->size) && !flag2 && !(**line))
		return (0);
	return (1);
}
