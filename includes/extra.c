/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_amount.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 13:41:01 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/30 18:04:39 by pde-bakk      ########   odam.nl         */
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
