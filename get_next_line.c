/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclock <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:09:01 by cclock            #+#    #+#             */
/*   Updated: 2020/12/14 04:31:42 by cclock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				find_n(char **stack, char **line)
{
	char	*new_line;
	char	*tmp_stack;

	new_line = ft_strchr(*stack, '\n');
	if (new_line)
	{
		new_line[0] = '\0';
		tmp_stack = *stack;
		*line = ft_strdup(tmp_stack);
		*stack = ft_strdup(&new_line[1]);
		free(tmp_stack);
		return (1);
	}
	else
		return (0);
}

int				read_fd(int fd, char *buf, char **stack, char **line)
{
	int		rd;
	int		flag;
	char	*tmp_stack;

	flag = 0;
	while (flag == 0 && (rd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rd] = '\0';
		if (!*stack)
			*stack = ft_strdup("");
		tmp_stack = *stack;
		*stack = ft_strjoin(tmp_stack, buf);
		free(tmp_stack);
		if (find_n(stack, line) == 1)
			flag = 1;
	}
	return (rd > 0 ? 1 : rd);
}

int				get_next_line(int fd, char **line)
{
	static char	*stack;
	int			rd;
	char		buf[BUFFER_SIZE + 1];

	if ((!line) || BUFFER_SIZE < 1 || read(fd, buf, 0) == -1)
		return (-1);
	if (stack)
		if (find_n(&stack, line))
			return (1);
	rd = read_fd(fd, buf, &stack, line);
	if (rd != 0 || !stack || !*stack)
	{
		if (rd == 0)
			*line = ft_strdup("");
		return (rd);
	}
	*line = stack;
	stack = NULL;
	return (rd);
}
