/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejuana <ejuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 20:42:52 by ejuana            #+#    #+#             */
/*   Updated: 2019/11/14 23:43:17 by ejuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	valid(char **stack, char **line)
{
	char	*tmp_stack;
	char	*strchr_stack;
	int		i;

	i = 0;
	strchr_stack = *stack;
	while (strchr_stack[i] != '\n')
		if (!strchr_stack[i++])
			return (0);
	tmp_stack = &strchr_stack[i];
	*tmp_stack = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(tmp_stack + 1);
	return (1);
}

static int	gnl_read(int fd, char *s1, char **stack, char **line)
{
	int		ret;
	char	*tmp_stack;

	while ((ret = read(fd, s1, BUFF_SIZE)) > 0)
	{
		s1[ret] = '\0';
		if(*stack)
		{
			tmp_stack = *stack;
			*stack = ft_strjoin(tmp_stack, s1);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*stack = NULL;
	}
	ret = (ret > 0) ? 1 : ret;
	return (ret);
}

int		ft_get_next_line(const int fd, char **line)
{
	return (0);
}

int	main(void)
{
	return (0);
}
