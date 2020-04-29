/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 17:47:03 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:50:24 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	write(fd, "\n", 1);
}
