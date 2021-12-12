/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:56:03 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/09 21:41:39 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*process_line(char **ret, char **s_buf)
{
	char	*n_buf;
	int		i;

	n_buf = NULL;
	i = 0;
	while ((*s_buf)[i] != '\n' && (*s_buf)[i])
		i++;
	if ((*s_buf)[i] == '\n')
	{
		i++;
		*ret = ft_substr(*s_buf, 0, i);
	}
	else if ((*s_buf)[i] == '\0' && *s_buf)
		*ret = ft_strdup(*s_buf);
	n_buf = ft_strdup(&(*s_buf)[i]);
	free(*s_buf);
	*s_buf = NULL;
	if (i == 0)
	{
		free(n_buf);
		n_buf = NULL;
		return (NULL);
	}
	return (n_buf);
}

static int	read_file(int fd, char *buf, char **s_buf)
{
	int		file;
	char	*tmp;

	if (!*s_buf)
		*s_buf = ft_strdup("");
	file = read(fd, buf, BUFFER_SIZE);
	while (file)
	{
		buf[file] = '\0';
		if (*s_buf)
		{
			tmp = *s_buf;
			*s_buf = ft_strjoin(*s_buf, buf);
			free(tmp);
		}
		else
			*s_buf = ft_substr(buf, 0, file);
		if (ft_strchr(buf, '\n'))
			break ;
		file = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	buf = NULL;
	return (file);
}

char	*get_next_line(int fd)
{
	int		    file;
	char		*buf;
	char		*ret;
	static char	*s_buf = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	file = read_file(fd, buf, &s_buf);
	s_buf = process_line(&ret, &s_buf);
	if (!file && !s_buf)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}
/*
int	main(int ac, char **av)
{
	int		fd;
	char    *gnl;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (0);
		while (1)
		{
			gnl = get_next_line(fd);
			if (gnl == NULL)
			{
				close(fd);
				exit (0);
			}
			printf("%s", gnl);
		}
		close(fd);
	}
	return (0);
}
*/