/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:31:26 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:48:43 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const char	*s;
	char		*d;

	s = (const char *)src;
	d = (char *)dst;
	while (n > 0)
	{
		if ((*s) == (char)c)
		{
			*d = *s;
			return (d + 1);
		}
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (NULL);
}
