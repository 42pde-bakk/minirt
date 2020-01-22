/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 13:23:26 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/22 13:49:59 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix    quat_to_matrix(t_quat quat)
{
    t_matrix    new;
    double      w;
    double      x;
    double      y;
    double      z;

    w = quat.w;
    x = quat.x;
    y = quat.y;
    z = quat.z;
    new.r.x = w * w + x * x - y * y - z * z;
    new.r.y = 2 * x * y - 2 * w * z;
    new.r.z = 2 * x * z + 2 * w * y;
    new.up.x = 2 * x * y + 2 * w * z;
    new.up.y = w * w - x * x + y * y - z * z;
    new.up.z = 2 * y * z + 2 * w * x;
    new.fw.x = 2 * x * z - 2 * w * y;
    new.fw.y = 2 * y * z - 2 * w * x;
    new.fw.z = w * w - x * x - y * y + z * z;
    return (new);
}

double	quat_sqrt(t_quat quat)
{
	double out;

	out = sqrt(quat.w * quat.w + quat.x * quat.x + quat.y * 
	quat.y + quat.z * quat.z);
	return (out);
}

t_quat	quat_norm(t_quat quat)
{
	double	m;
	t_quat	out;

	m = quat_sqrt(quat);
	out.w /= m;
	out.x /= m;
	out.y /= m;
	out.z /= m;
	return (out);
}

t_quat	quat_mult(t_quat a, t_quat b)
{
    t_quat  new;

    new.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    new.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    new.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    new.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (new);
}

t_quat		quat_init(double w, double x, double y, double z)
{
	t_quat	out;

	out.w = w;
	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

t_quat		quat_new(double x, double y, double z, double angle)
{
    t_quat  new;
    angle = deg2rad(angle);
    new.w = cos(angle);
    new.x = x * sin(angle);
    new.y = y * sin(angle);
    new.z = z * sin(angle);
    return (new);
}

t_quat		quat_lookat_peer(t_vec3 position, t_vec3 dirv)
{
	t_vec3	axis;
	t_quat	quat;
	double	angle;
	double	normal;

	(void)position;
	angle = acos(dotproduct(vec3_new(0.0, 0.0, 1.0), dirv));
	// printf("angle = %f\n", angle);
	axis = crossproduct(vec3_new(0.0, 0.0, 1.0), dirv);
	axis = vec3_normalize(axis);
	// printf("axis_sqr=%f\n", vec3_sqr(axis));
	if (vec3_sqr(axis) > -EPSILON && vec3_sqr(axis) < EPSILON)
		axis = vec3_new(0.0, 1.0, 0.0);
	normal = sqrt(1.0 / (pow(cos(angle * 0.5), 2.0) + pow(axis.x \
			* sin(angle * 0.5), 2.0) + pow(axis.y * sin(angle * 0.5), 2.0) \
			+ pow(axis.z * sin(angle * 0.5), 2.0)));

	// quat = quat_new(axis.x, axis.y, axis.z, rad2deg(angle));
	quat = quat_new(axis.x * normal, axis.y * normal, axis.z * normal, rad2deg(angle));
	return (quat);
}

int			nancheck(t_vec3 vec)
{
	if (vec.x != vec.x || vec.y != vec.y || vec.z != vec.z)
		return (1);
	else
		return (0);
}

t_quat		quat_lookat(t_vec3 to, t_vec3 from)
{
    double  angle;
    t_vec3   up;

    angle = acos(dotproduct(vec3_normalize(to), vec3_normalize(from)));
    up = vec3_normalize(crossproduct(from, to));
	if (nancheck(up) == 1)
		up = vec3_new(0.0, 1.0, 0.0);
	printvec(up, "vecUP");
    return (quat_new(up.x, up.y, up.z, rad2deg(angle)));
}

// t_quat	quat_angle(t_vec3 angle)
// {
// 	t_quat	qx;
// 	t_quat	qy;
// 	t_quat	qz;
// 	t_quat	out;

// 	qx = quat_new(cos(angle.x / 2), 0.0, 0.0, sin(angle.x / 2));
// 	qy = quat_new(cos(angle.y / 2), 0.0, sin(angle.y / 2), 0.0);
// 	qz = quat_new(cos(angle.z / 2), sin(angle.z / 2), 0.0, 0.0);
	
// 	out = quat_mult(qx, qy);
// 	out = quat_mult(out, qz);
// 	return (out);
// }

t_matrix	quaternion_rotation_matrix(t_quat q)
{
	t_matrix	quatmat;

	q = quat_norm(q);
	quatmat.r.x = 1 - 2 * (q.y * q.y + q.z * q.z);
	quatmat.r.y = 2 * (q.x * q.y - q.z * q.w);
	quatmat.r.z = 2 * (q.x * q.z + q.y * q.w);

	quatmat.up.x = 2 * (q.x * q.y + q.z * q.w);
	quatmat.up.y = 1 - 2 * (q.x * q.x + q.z * q.z);
	quatmat.up.z = 2 * (q.y * q.z - q.x * q.w);

	quatmat.fw.x = 2 * (q.x * q.z - q.y * q.w);
	quatmat.fw.y = 2 * (q.y * q.z + q.x * q.w);
	quatmat.fw.z = 1 - 2 * (q.x * q.x + q.y * q.y);
	return (quatmat);
}

void		printquat(t_quat quat, char *str)
{
	printf("%s:\n", str);
	printf("quat.w=%f\n", quat.w);
	printf("quat.x=%f\n", quat.x);
	printf("quat.y=%f\n", quat.y);
	printf("quat.z=%f\n", quat.z);
}
t_matrix    ft_newrotate(t_data *my_mlx, t_vec3 angle)
{
    t_quat  res;
	if (angle.x > 0.0 || angle.x < 0)
		res = quat_new(1.0, 0.0, 0.0, angle.x);
	else if (angle.y > 0.0 || angle.y < 0)
		res = quat_new(0.0, 1.0, 0.0, angle.y);
	else if (angle.z > 0.0 || angle.z < 0)
		res = quat_new(0.0, 0.0, 1.0, angle.z);
	else
		res = quat_new(0.0, 0.0, 0.0, 0.0);
    my_mlx->cam->quat = quat_mult(res, my_mlx->cam->quat);
	// printvec(my_mlx->cam->v, "cam->v in quatrot");
	// printquat(my_mlx->cam->quat, "quat after rotation is");
    return (quat_to_matrix(my_mlx->cam->quat));
}
