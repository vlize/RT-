/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 10:39:07 by vlize             #+#    #+#             */
/*   Updated: 2014/11/27 17:23:53 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*text_end(char const *s1)
{
	size_t	i;
	size_t	l;
	char	*s2;
	char	*tmp;

	i = 0;
	tmp = (char *)s1;
	l = ft_strlen(tmp);
	s2 = (char *)malloc(sizeof(*s2) * (l + 2));
	if (!s2)
		return (NULL);
	while (i <= l)
	{
		s2[i] = tmp[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static int	search_next_line(char **line, char **lfd)
{
	size_t	l;
	char	*tmp;

	l = ft_strlen(*lfd) + 1;
	if ((*lfd)[l] == '\0')
	{
		free(*lfd);
		*lfd = NULL;
		*line = NULL;
		return (0);
	}
	tmp = text_end(&((*lfd)[l]));
	if (!tmp)
		return (-1);
	free(*lfd);
	*lfd = tmp;
	return (1);
}

static int	start_line(char **line, char **lfd)
{
	size_t	i;

	if ((*lfd)[0] == '\0')
	{
		free(*lfd);
		*lfd = NULL;
		*line = NULL;
		return (0);
	}
	i = 0;
	while (((*lfd)[i] != '\n') && ((*lfd)[i] != '\0'))
		i++;
	(*lfd)[i] = '\0';
	*line = *lfd;
	return (1);
}

static int	make_text(int const fd, char **lfd)
{
	intmax_t	i;
	char		*tmp;
	char		buf[BUFF_SIZE];

	lfd[fd] = (char *)malloc(sizeof(char) * 1);
	if (!(lfd[fd]))
		return (-1);
	(lfd[fd])[0] = '\0';
	i = read(fd, buf, BUFF_SIZE);
	if (i < 1)
		return ((int)i);
	while (i > 0)
	{
		buf[i] = '\0';
		if ((ft_strlen(lfd[fd]) + ft_strlen(buf) + 1) > (size_t)(-1))
			return (-1);
		tmp = ft_strjoin(lfd[fd], buf);
		if (!tmp)
			return (-1);
		ft_free(lfd[fd]);
		lfd[fd] = tmp;
		i = read(fd, buf, BUFF_SIZE);
	}
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	int			i;
	static char	*lfd[FD_SETSIZE];

	if ((fd < 0) || (fd > FD_SETSIZE) || !line)
		return (-1);
	if (!lfd[fd])
	{
		i = make_text(fd, lfd);
		if (i < 0)
			return (i);
		i = 1;
	}
	else
	{
		i = search_next_line(line, &(lfd[fd]));
		if (i < 1)
			return (i);
	}
	if (i < 1)
		return (i);
	i = start_line(line, &(lfd[fd]));
	return (i);
}
