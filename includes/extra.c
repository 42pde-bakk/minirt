/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_amount.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 13:41:01 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/27 14:49:05 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_amount(long int nb)
{
	long	amount;

	amount = 0;
	if (nb == 0)
		amount++;
	if (nb < 0)
	{
		amount++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		amount++;
	}
	return (amount);
}

int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
	|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_objectcheck(const char *id)
{
	if (ft_strncmp(id, "sp", 2) == 0)
		return (1);
	else if (ft_strncmp(id, "pl", 2) == 0)
		return (2);
	else if (ft_strncmp(id, "sq", 2) == 0)
		return (3);
	else if (ft_strncmp(id, "cy", 2) == 0)
		return (4);
	else if (ft_strncmp(id, "tr", 2) == 0)
		return (5);
	else
		return (0);
}
