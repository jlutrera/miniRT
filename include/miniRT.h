/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:06:47 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/18 12:25:16 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include <math.h>
# include <limits.h>
// # include <double.h>
//Windows
# include "../mlx_linux/mlx.h"
// # include <X11/Xlib.h>
//Mac
//# include <mlx.h>

// COLORS
# define P_RED   	0xFF0000
# define P_GREEN 	0x00FF00
# define P_BLUE  	0x0000FF
# define P_WHITE 	0xFFFFFF
# define P_YELLOW	0xFFFF00
# define P_CYAN 	0x4BB5FF

//KEYCODE para Windows
 # define K_ESC		0xFF1B
 # define K_UP		0xFF52
 # define K_DOWN	0xFF54
 # define K_LEFT	0xFF51
 # define K_RIGHT	0xFF53
 # define K_W		119
 # define K_S		115
 # define K_A		97
 # define K_D		100
 # define M_B_R		3

//KeyCodes for Mac
/*# define K_ESC   	53
# define K_UP    	126
# define K_DOWN  	125
# define K_LEFT  	123
# define K_RIGHT 	124
# define K_W 		13
# define K_S 		1
# define K_A 		0
# define K_D 		2
# define M_B_R		2*/

//KeyCode for both OS
# define M_B_CDOWN	4
# define M_B_CUP	5
# define M_B_L		1

//Window Size for the image
# define WIDTH		500
# define HEIGHT		500

//STRUCTS

typedef struct s_vars
{
    void	*mlx;
    void	*win;
} t_vars;

typedef struct s_vec
{
    double	x;
	double	y;
	double	z;
} t_vec;

typedef struct s_point3
{
    double	x;
	double	y;
	double	z;
} t_point3;

typedef struct s_point
{
    double	x;
	double	y;
} t_point;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_sphere
{
    t_point3	center;
    double		radius;
	t_color		color;
} t_sphere;

typedef struct s_plane
{
	t_point3	coordenate;
	t_vec		direction;
	t_color		color;
} t_plane;

typedef struct s_cylinder
{
	t_point3	coordenate;
	t_vec		direction;
	double		radius;
	double		height;
	t_color		color;
} t_cylinder;

typedef struct s_ambient
{
	bool		declared;
	double		ratio;
	t_color		color;
} t_ambient;

typedef struct s_camera
{
	bool		declared;
	t_point3	position;
	t_vec		direction;
	int			fov;
} t_camera;

typedef	struct s_light
{
	bool		declared;
	t_point3	position;
	double		bright;
	t_color		color;
} t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere*	spheres;
	int			nb_sp;
	t_plane*	planes;
	int			nb_pl;
	t_cylinder*	cylinders;
	int			nb_cy;
} t_scene;

//PROTOTYPES
//void	process_img(char *name);
//void	my_hooks(t_vars *vars);
int		process_file(char *file, t_scene *scene);

#endif