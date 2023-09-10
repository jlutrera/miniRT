/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:47:04 by jutrera-          #+#    #+#             */
/*   Updated: 2023/02/27 22:47:04 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include <math.h>
# include <limits.h>
# include <float.h>
//Windows
# include "../mlx_linux/mlx.h"
# include <X11/Xlib.h>
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
 # define K_ESC   	0xFF1B
 # define K_UP    	0xFF52
 # define K_DOWN  	0xFF54
 # define K_LEFT  	0xFF51
 # define K_RIGHT 	0xFF53
 # define K_W 		119
 # define K_S 		115
 # define K_A 		97
 # define K_D 		100
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
# define WIDTH   	500
# define HEIGHT   	500

//STRUCTS

typedef struct {
    void *mlx;
    void *win;
} t_vars;

typedef struct {
    float x;
	float y;
	float z;
} t_point3d;

typedef struct {
    int	x;
	int	y;
} t_point;

typedef struct {
	int	r;
	int	g;
	int	b;
} t_colour;

typedef struct {
    t_point3d	center;
    float		radius;
	t_colour	colour;
} t_sphere;

typedef struct {
	t_point3d	coordenate;
	t_point3d	direction;
	t_colour	colour;
} t_plane;

typedef struct {
	t_point3d	coordenate;
	t_point3d	direction;
	float		radius;
	float		height;
	t_colour	colour;
} t_cylinder;

typedef struct {
	bool		declared;
	float		ratio;
	t_colour	colour;
} t_ambient;

typedef struct {
	bool		declared;
	t_point3d	position;
	t_point3d	direction;
	int			fov;
} t_camera;

typedef	struct {
	bool		declared;
	t_point3d	position;
	float		bright;
	t_colour	colour;
} t_light;

typedef struct {
	t_ambient 	ambient;
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