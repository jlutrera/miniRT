/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:55:43 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 18:09:51 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_image;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
}				t_point3;

typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray
{
	t_point3	origin;
	t_vec		dir;
}				t_ray;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_point3	coordinate;
	t_vec		direction;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	coordinate;
	t_vec		direction;
	double		radius;
	double		height;
	t_color		color;
}				t_cylinder;

typedef enum s_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER,
}			t_obj_type;

typedef struct s_lst_obj
{
	void				*object;
	t_obj_type			type;
	double				last_dist;
	bool				skip;
	struct s_lst_obj	*next;
}				t_lst_obj;

typedef struct s_ambient
{
	bool		declared;
	double		ratio;
	t_color		color;
}				t_ambient;

typedef struct s_camera
{
	bool		declared;
	t_point3	position;
	t_vec		direction;
	int			fov;
	t_point3	viewp;
}				t_camera;

typedef struct s_light
{
	bool		declared;
	t_point3	position;
	double		bright;
	t_color		color;
}				t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_lst_obj	*obj;
}				t_scene;

typedef struct s_data
{
	t_vars	vars;
	t_image	image;
}				t_data;

#endif
