/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 13:41:01 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:50:59 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_amount(long int nb)
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

void	fswap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return ;
}
