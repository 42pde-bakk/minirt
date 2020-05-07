/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacle_cylinder.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 19:12:39 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/05/07 06:09:17 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_cylhelp	cylinder_calc(t_cylinder *cyl, t_vec3 hitpos,
						t_vec3 lightdir)
{
	t_cylhelp	help;

	help.rayorigin = hitpos;
	help.raydir = lightdir;
	help.cylcenter = cyl->s;
	help.cylrot = cyl->v;
	help.dist = vec3_sub(help.rayorigin, help.cylcenter);
	help.c1 = vec3_sub(help.raydir, vec3_mult(help.cylrot,
	dotproduct(help.raydir, help.cylrot)));
	help.c2 = vec3_sub(help.dist, vec3_mult(help.cylrot,
	dotproduct(help.dist, help.cylrot)));
	help.abc0 = vec3_sqr(help.c1);
	help.abc1 = 2.0 * dotproduct(help.c1, help.c2);
	help.abc2 = vec3_sqr(help.c2) - pow((cyl->diameter / 2), 2);
	help.p1 = vec3_sub(help.cylcenter, vec3_mult(help.cylrot,
	cyl->height / 2.0));
	help.p2 = vec3_add(help.cylcenter, vec3_mult(help.cylrot,
	cyl->height / 2.0));
	return (help);
}

static int			quadratic_equation_solve(t_cylhelp *help)
{
	double	discriminant;

	discriminant = pow(help->abc1, 2) - 4.0 * help->abc0 * help->abc2;
	if (discriminant < 0.0)
		return (0);
	else if (discriminant < EPSILON)
	{
		help->t0 = -0.5 * help->abc1 / help->abc0;
		help->t1 = help->t0;
	}
	else
	{
		help->t0 = (-help->abc1 + sqrt(discriminant)) / (2.0 * help->abc0);
		help->t1 = (-help->abc1 - sqrt(discriminant)) / (2.0 * help->abc0);
	}
	return (1);
}

void				get_dotp(t_cylhelp help, double dotp[4])
{
	t_vec3	q;

	q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.t0));
	dotp[0] = dotproduct(help.cylrot, vec3_sub(q, help.p1));
	dotp[1] = dotproduct(help.cylrot, vec3_sub(q, help.p2));
	q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.t1));
	dotp[2] = dotproduct(help.cylrot, vec3_sub(q, help.p1));
	dotp[3] = dotproduct(help.cylrot, vec3_sub(q, help.p2));
}

int					obstacle_cylinder(t_cylinder *cyl, t_vec3 hitpos,
						t_vec3 lightdir, double distance)
{
	t_cylhelp	help;
	double		res;
	double		dotp[4];

	help = cylinder_calc(cyl, hitpos, lightdir);
	res = -1.0;
	if (quadratic_equation_solve(&help) == 1)
	{
		get_dotp(help, dotp);
		if (help.t0 > 0.0 && dotp[0] > 0.0 && dotp[1] < 0.0)
			res = help.t0;
		if (help.t1 > 0.0 && dotp[2] > 0.0 && dotp[3] < 0.0)
		{
			if (res != -1.0)
				res = fmin(help.t0, help.t1);
			else
				res = help.t1;
		}
		if (res < distance && res > 0.0)
			return (1);
	}
	return (0);
}

int					cylinders_loopover(t_data *my_mlx, t_vec3 hitpos,
						t_vec3 lightdir, double distance)
{
	t_cylinder	*tmpcylinder;

	tmpcylinder = my_mlx->cylinder;
	while (tmpcylinder)
	{
		if (obstacle_cylinder(tmpcylinder, hitpos, lightdir, distance) == 1)
			return (1);
		tmpcylinder = tmpcylinder->next;
	}
	return (0);
}
