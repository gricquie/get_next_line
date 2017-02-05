/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 15:59:25 by gricquie          #+#    #+#             */
/*   Updated: 2017/01/06 17:46:58 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_line	*select_fd(t_line *begin, int fd)
{
	if (!begin)
	{
		if (!(begin = (t_line *)ft_memalloc(sizeof(t_line))))
			return (NULL);
		begin->fd = fd;
		begin->next = NULL;
		begin->size = 0;
		begin->i = 0;
		if (!(begin->line = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (NULL);
	}
	while (begin->fd != fd && begin->next != NULL)
		begin = begin->next;
	if (begin->fd == fd)
		return (begin);
	begin->next = select_fd(begin->next, fd);
	return (begin->next);
}

static void		fill_buff(t_line *buff)
{
	if (buff->line && buff->i >= buff->size)
	{
		buff->i = 0;
		buff->size = read(buff->fd, buff->line, BUFF_SIZE);
		buff->line[buff->size] = '\0';
	}
}

static int		fill_line(t_line *buff, char **line)
{
	int		i;

	i = 0;
	if (!line)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char))))
		return (-1);
	while (buff->i < buff->size && (buff->line)[buff->i] != '\n')
	{
		if (!(*line = (char *)ft_realloc(*line, sizeof(char) * (i + 2))))
			return (-1);
		(*line)[i] = buff->line[buff->i];
		i++;
		(buff->i)++;
		fill_buff(buff);
	}
	(*line)[i] = '\0';
	if (buff->i < buff->size)
		(buff->i)++;
	return (0);
}

static void		ft_linedeljoin(t_line **del, t_line *begin)
{
	t_line	*lst;

	lst = begin;
	if (del == NULL || *del == NULL)
		return ;
	if (begin == *del)
	{
		lst = lst->next;
		if ((*del)->line)
			ft_strdel(&((*del)->line));
		free(*del);
		*del = lst;
		return ;
	}
	while (begin && begin->next != *del && begin->next != NULL)
		begin = begin->next;
	if (begin && begin->next == *del)
		begin->next = (*del)->next;
	if ((*del)->line)
		ft_strdel(&((*del)->line));
	free(*del);
	*del = lst;
}

int				get_next_line(const int fd, char **line)
{
	static	t_line	*buff = NULL;
	t_line			*begin;

	if (line == NULL)
		return (-1);
	begin = buff;
	if (fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!(buff = select_fd(buff, fd)) || read(fd, buff->line, 0) == -1)
		return (-1);
	fill_buff(buff);
	if (buff && buff->size == 0)
	{
		ft_strdel(&buff->line);
		ft_linedeljoin(&buff, begin);
		return (0);
	}
	if (fill_line(buff, line) == -1)
		return (-1);
	if (begin)
		buff = begin;
	return (1);
}
