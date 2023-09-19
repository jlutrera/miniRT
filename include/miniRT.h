/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:06:47 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/19 13:30:32 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include <math.h>
# include <limits.h>
# include "./errors.h"
# include "./keycodes.h"
// # include <double.h>
//Windows
# include "../mlx_linux/mlx.h"
// # include <X11/Xlib.h>
//Mac
//# include <mlx.h>

//Window Size for the image
# define WIDTH   	1280
# define HEIGHT   	720

//STRUCTS

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

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
}		t_color;

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
	t_point3	coordenate;
	t_vec		direction;
	t_color		color;
} 				t_plane;

typedef struct s_cylinder
{
	t_point3	coordenate;
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

//PROTOTYPES
//void	process_img(char *name);
void	my_hooks(t_vars *vars);
int		process_file(char *file, t_scene *scene, int *n);

//Vectors
t_vec vec(double x, double y, double z);

//Errors
int	ft_errormsg(int e, int n);

#endif