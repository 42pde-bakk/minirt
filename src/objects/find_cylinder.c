/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cylinder.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:05:36 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/27 18:05:52 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int		find_cylinder(t_data *my_mlx)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;

// 	// R(t) = o + td
// 	// x² + z² = r²
// 	// (ox+tdx)² + (oz+tdz)² = r²
// 	// (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
// 	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
// 	// a=(dx + dz); b = 2(oxdx + ozdz); c = (ox)² + (oz)² - r²

// 	a = pow(my_mlx->ray->v.x, 2) + pow(my_mlx->ray->v.z, 2);
// 	b = 2 * pow(my_mlx->ray->v.x, 2) + 2 * pow(my_mlx->ray->v.y, 2);
// 	c = a - 1;
// 	discriminant = pow(b, 2) - (4 * a * c);

// }
