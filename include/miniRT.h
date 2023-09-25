/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:06:47 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/25 18:28:49 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include <math.h>
# include <limits.h>
# include "./errors.h"
# include "./keycodes.h"

//Windows
# include "../mlx_linux/mlx.h"
//# include <X11/Xlib.h>
//Mac
//# include <mlx.h>

//Window Size for the image
# define WIDTH   	1280
# define ASPECT_RATIO 16.0 / 9.0
# define M_PI 3.14159265358979323846
# define EPSILON 0.000001

//STRUCTS

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
} 			t_image;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
}			t_point3;

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
} 				t_sphere;

typedef struct s_plane
{
	t_point3	coordinate;
	t_vec		direction;
	t_color		color;
} 				t_plane;

typedef struct s_cylinder
{
	t_point3	coordinate;
	t_vec		direction;
	double		radius;
	double		height;
	t_color		color;
} 				t_cylinder;

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
} 				t_lst_obj;

typedef struct s_ambient
{
	bool		declared;
	double		ratio;
	t_color		color;
} 				t_ambient;

typedef struct s_camera
{
	bool		declared;
	t_point3	position;
	t_vec		direction;
	int			fov;
	t_point3	viewp;
} 				t_camera;

typedef	struct s_light
{
	bool		declared;
	t_point3	position;
	double		bright;
	t_color		color;
} 				t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_lst_obj	*obj;
} 				t_scene;

typedef struct 	s_data
{
	t_vars	vars;
	t_image	image;
}				t_data;

//PROTOTYPES
void		my_hooks(t_vars *vars);
int			process_file(char *file, t_scene **scene, int *n);
void		process_img(t_data *data, t_scene *scene);

//Vectors
t_vec 		vec(double x, double y, double z);
t_vec		vec_add (t_vec v1 , t_vec v2);
t_vec		vec_sub (t_vec v1 , t_vec v2);
t_vec		vec_mul(t_vec v, double t);
t_vec		vec_cal(t_vec *v, double *a, int n);

double 		vec_dot(t_vec v1, t_vec v2);
t_vec 		vec_cross(t_vec v1,t_vec v2);
double 		vec_length(t_vec v);
t_vec 		vec_unit(t_vec v);
t_vec		vec_divition(t_vec v1, double t);

//Ray
t_vec		ray_ex(t_ray *ray , double t);
t_ray 		ray(t_point3 origin, t_vec dir);

//Colour
int 		get_rgb(t_color c);
int			write_color(t_point3 pixel_color);

//Errors
int			ft_errormsg(int e, int n);

#endif