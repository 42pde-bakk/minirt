/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_int.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 18:37:05 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/25 18:40:48 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int				ft_putstr_int(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
	return (0);
}
