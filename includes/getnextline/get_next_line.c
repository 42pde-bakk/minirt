/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 15:02:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2019/12/06 16:10:25 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

int		ft_newlinecheck(char *str, int k)
{
	int	i;

	i = 0;
	if (k == 0 || k == 1)
		while (str[i])
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	if (k == 1)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (-1);
}

char	*ft_bufferfixer(char *buf)
{
	int i;
	int len;

	i = 0;
	len = ft_newlinecheck(buf, 0) + 1;
	while (buf[i] && buf[len + i])
	{
		buf[i] = buf[len + i];
		i++;
	}
	while (buf[i])
	{
		buf[i] = 0;
		i++;
	}
	return (buf);
}

int		ft_the_finisher(char *str, char *buf, char **line, int ret)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n' || str[i] == 0)
			break ;
		i++;
	}
	*line = ft_strdup(str, i, 0);
	if (str)
		free(str);
	if (ret == 0 && buf)
	{
		free(buf);
		buf = NULL;
		return (0);
	}
	else
	{
		ft_bufferfixer(buf);
		return (1);
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*buf[OPEN_MAX];
	char		*str;
	int			ret;

	ret = 1;
	str = ft_calloc(0, 0);
	if (!buf[fd])
		buf[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buf[fd] != NULL && buf[fd][0] != 0)
		ret = ft_strlen(buf[fd]);
	while (ret > 0)
	{
		str = ft_strjoiner(str, buf[fd], ret);
		if (ft_newlinecheck(str, 0) > -1)
			return (ft_the_finisher(str, buf[fd], line, ret));
//		free(buf);
		ft_bzero(buf[fd], BUFFER_SIZE + 1);
//		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (ret == -1)
			return (ret);
	}
	if (ret == 0)
		return (ft_the_finisher(str, buf[fd], line, ret));
	return (0);
}
