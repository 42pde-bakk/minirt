/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 18:29:13 by pde-bakk       #+#    #+#                */
/*   Updated: 2019/12/30 17:04:27 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static int	ft_amount(long long nb, long long base)
{
	long long	amount;

	amount = 0;
	if (nb == 0)
		amount++;
	if (nb < 0 && base == 10)
	{
		amount++;
		nb = -nb;
	}
	while (nb)
	{
		nb = nb / base;
		amount++;
	}
	return (amount);
}

static int	ft_absolutely(long long nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

char		*ft_itoa_base(long long nb, long long base)
{
	char	*str;
	char	*tab;
	int		amount;

	amount = ft_amount(nb, base);
	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (base < 2 || base > 36)
		return (0);
	str = (char*)ft_calloc(amount + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (amount > 0)
	{
		str[amount - 1] = tab[ft_absolutely(nb % base)];
		amount--;
		nb = nb / base;
	}
	return (str);
}
