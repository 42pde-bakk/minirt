/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:06:06 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/08 13:55:57 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*vector_subtractor(double *v1, double *v2, double *ret)
{
	int		i;

	i = 0;
	while (/*v1[i] && v2[i] &&*/i < 3)
	{
		ret[i] = v1[i] - v2[i];
		i++;
//		printf("vector_subtractor gives: {%f, %f, result=%f}\n", v1[i], v2[i], ret[i]);
	}
	return (ret);
}

double	*vector_add(double *v1, double *v2, double *ret)
{
	int		i;

	i = 0;
	while (/*v1[i] && v2[i] &&*/ i < 3)
	{
		ret[i] = v1[i] + v2[i];
//		printf("vector_add gives: {%f, %f, result=%f}\n", v1[i], v2[i], ret[i]);
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
	while (/*v1[i] && v2[i] &&*/i < 3)
	{
		ret += v1[i] * v2[i];
//		printf("dotproduct gives: {%f, %f, result=%f}\n", v1[i], v2[i], ret);
		i++;
	}
//	printf("ehhe\n");
	return (ret);
}

double	*doublemapi(double *v1, double d, double *ret)
{
	int	i;

	i = 0;
	while (/*v1[i] && */i < 3)
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
