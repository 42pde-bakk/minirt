/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:06:06 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/09 14:24:39 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*vector_sub(double *v1, double *v2, double *ret)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		ret[i] = v1[i] - v2[i];
		i++;
	}
	return (ret);
}

void	trianglecross(t_data *my_mlx, double *ret)
{
	double *v1;
	double *v2;

	v1 = NULL;
	v2 = NULL;
	printf("hehe\n");
	printf("s1={%f, %f, %f}\n", my_mlx->triangle->s1[0], my_mlx->triangle->s1[1], my_mlx->triangle->s1[2]);
	printf("s2={%f, %f, %f}\n", my_mlx->triangle->s2[0], my_mlx->triangle->s2[1], my_mlx->triangle->s2[2]);
	printf("s3={%f, %f, %f}\n", my_mlx->triangle->s3[0], my_mlx->triangle->s3[1], my_mlx->triangle->s3[2]);
	v1 = vector_sub(my_mlx->triangle->s2, my_mlx->triangle->s1, v1);
	printf("debug\n");
	v2 = vector_sub(my_mlx->triangle->s3, my_mlx->triangle->s1, v2);

	printf("wtf\n");
	ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
	ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
	ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

double	*crossproduct(double *v1, double *v2, double *ret)
{
	ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
	ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
	ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return (ret);
}

double	*vector_add(double *v1, double *v2, double *ret)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		ret[i] = v1[i] + v2[i];
		i++;
	}
	return (ret);
}

double	dotproduct(double *v1, double *v2)
{
	int		i;
	double	ret;

	ret = 0.0;
	i = 0;
	while (i < 3)
	{
		ret += v1[i] * v2[i];
		i++;
	}
	return (ret);
}

double	*doublemapi(double *v1, double d, double *ret)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		ret[i] = v1[i] * d;
		i++;
	}
	return (ret);
}

double	find_length(double *s, double *p)
{
	double	ret;
	double	retx;
	double	rety;
	double	retz;

	retx = pow(s[0] - p[0], 2);
	rety = pow(s[1] - p[1], 2);
	retz = pow(s[2] - p[2], 2);
	ret = sqrt(retx + rety + retz);
	return (ret);
}
