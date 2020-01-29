/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cylinder.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:05:36 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/29 17:20:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylhelp	cylinder_calc(t_cylinder *cyl, t_data *my_mlx)
{
	t_cylhelp	help;

	help.rayorigin = my_mlx->cam->s; //rayorigin
	help.raydir = my_mlx->ray->v; //raydirection
	help.cylcenter = cyl->s; //cylinder center
	help.cylrot = cyl->v; //cyl
	help.dist = vec3_sub(help.rayorigin, help.cylcenter);
	help.c1 = vec3_sub(help.raydir, vec3_mult(help.cylrot, dotproduct(help.raydir, help.cylrot)));
	help.c2 = vec3_sub(help.dist, vec3_mult(help.cylrot, dotproduct(help.dist, help.cylrot)));
	help.abc0 = vec3_sqr(help.c1);
	help.abc1 = 2.0 * dotproduct(help.c1, help.c2);
	help.abc2 = vec3_sqr(help.c2) - pow((cyl->diameter / 2), 2);
	help.p1 = vec3_sub(help.cylcenter, vec3_mult(help.cylrot, cyl->height / 2.0));
	help.p2 = vec3_add(help.cylcenter, vec3_mult(help.cylrot, cyl->height / 2.0));

	return (help);
}

/*
** If Discriminant = 0 there is 1 solution, if D>0 there are 2, if D<0 there are none
*/
int		solve_quadratic_equation(t_cylhelp *help)
{
	double	discriminant;

	discriminant = pow(help->abc1, 2) - 4.0 * help->abc0 * help->abc2; //bˆ2- 4*a*c
	if (discriminant < 0.0)
		return (0);
	else if (discriminant < EPSILON)
	{
		help->y0 = -0.5 * help->abc1 / help->abc0;
		help->y1 = help->y0;
	}
	else
	{
		help->y0 = (-help->abc1 + sqrt(discriminant)) / (2.0 * help->abc0);
		help->y1 = (-help->abc1 - sqrt(discriminant)) / (2.0 * help->abc0);
	}
	return (1);
}

int		find_cylinder(t_cylinder *cyl, t_data *my_mlx)
{
	t_cylhelp	help;
	t_vec3		q;
	double		res;
	double		dotp1;
	double		dotp2;
	
	res = -1;
	help = cylinder_calc(cyl, my_mlx);
	if (solve_quadratic_equation(&help) == 1)
	{
		q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.y0));
		dotp1 = dotproduct(help.cylrot, vec3_sub(q, help.p1));
		dotp2 = dotproduct(help.cylrot, vec3_sub(q, help.p2));
		if (help.y0 > 0.0 && dotp1 > 0.0 && dotp2 < 0.0)
			res = help.y0;
		q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.y1));
		if (help.y1 > 0.0 && dotp1 > 0.0 && dotp2 < 0.0)
		{
			if (res != -1)
				res = fmin(help.y0, help.y1);
			else
				res = help.y1;
			if ((res < my_mlx->ray->length || my_mlx->ray->length == 0.0))
			{
				my_mlx->ray->length = res;
				my_mlx->ray->colour = cyl->colour;
				my_mlx->ray->hitnormal = vec3_normalize(vec3_sub(cyl->s, vec3_mult(my_mlx->ray->v, res)));
			}
		}
		return (res);		
	}
	return (0);
}
