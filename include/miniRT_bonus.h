/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:06:47 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/21 11:14:27 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../libft/include/libft.h"
# include <math.h>
# include <limits.h>
# include "./errors.h"
# include "./structs_bonus.h"

# ifdef __APPLE__
#  include <mlx.h>
#  define K_ESC   	53
#  define K_LEFT  	123
#  define K_RIGHT 	124
# else
#  include "../mlx_linux/mlx.h"
#  define K_ESC   	0xFF1B
#  define K_LEFT  	0xFF51
#  define K_RIGHT 	0xFF53
# endif

//Window Size for the image
# define WIDTH 1080
# define ASPECT_RATIO 1.78  //16:9
# define EPSILON 0.000001
# define SPECULAR 100

//my_hooks.c
void		my_hooks(t_data *vars);
void		free_memory(t_scene *scene);

//process_file.c
int			process_file(char *file, t_scene **scene, int *n);

//parser.c
int			parse_line(char *line, t_scene **scene);

//Vec_operations1.c
t_vec		vec(double x, double y, double z);
t_vec		vec_add(t_vec v1, t_vec v2);
t_vec		vec_sub(t_vec v1, t_vec v2);
t_vec		vec_mul(t_vec v, double t);
t_vec		vec_rotate(t_vec v, t_vec d);

//Vec_operations2.c
double		vec_dot(t_vec v1, t_vec v2);
t_vec		vec_cross(t_vec v1, t_vec v2);
double		vec_length(t_vec v);
t_vec		vec_unit(t_vec v);
t_vec		vec_divition(t_vec v1, double t);

//vec_operations3.c
t_vec		point_to_vec(t_point3 P);
t_point3	vec_to_point(t_vec v);

//Ray.c
t_vec		ray_ex(t_ray *ray, double t);
t_ray		ray(t_point3 origin, t_vec dir);

//Colour
int			get_rgb(t_color c);
int			write_color(t_point3 pixel_color);

//print_errors.c
int			ft_errormsg(int e, int n);

//process_img.c
void		process_img(t_data *data, t_scene *scene);

//light_shadow.c
t_point3	compute_shadows(t_scene scene, t_vec p, t_vec n);
t_point3	compute_colour_lighting(t_scene scene, t_vec p, t_vec n);

//sphere.c
void		intersect_sp(t_ray ray, t_sphere *sp, t_point *t);
t_point3	compute_sp_colour_light(t_sphere *sp, t_scene scene, t_vec p);
t_sphere	*new_sp(char **s, int *e);
int			ft_load_sp(t_lst_obj **obj, char **s);

//plane.c
void		intersect_pl(t_ray ray, t_plane *plane, t_point *t);
t_point3	compute_pl_colour_light(t_plane *pl, t_scene scene, t_vec p);
int			ft_load_pl(t_lst_obj **obj, char **s);
t_plane		*new_pl(char **s, int *e);

//cylinder.c
t_point3	compute_cy_colour_light(t_cylinder *cy, t_scene scene, t_vec p);
int			ft_load_cy(t_lst_obj **obj, char **s);
t_cylinder	*new_cy(char **s, int *e);

//cylinder2.c
void		intersect_cy(t_ray ray, t_cylinder *cy, t_point *t);

//triangle.c
void		intersect_tr(t_ray ray, t_triangle *tr, t_point *t);
t_point3	compute_tr_colour_light(t_triangle *tr, t_scene scene, t_vec p);
int			ft_load_tr(t_lst_obj **obj, char **s);
t_triangle	*new_tr(char **s, int *e);

//cone2.c
void		intersect_co(t_ray ray, t_cone *co, t_point *t);

//cone.c
t_point3	compute_co_colour_light(t_cone *co, t_scene scene, t_vec p);
int			ft_load_co(t_lst_obj **obj, char **s);
t_cone		*new_co(char **s, int *e);

//parser_utils.c
double		ft_get_dist(void);
int			is_normalized(t_vec vector);
double		ft_atod(char *s);
int			check_comps(char **s, int n);

//parser_gets.c
int			ft_get_vector(char *s, t_vec *direction);
int			ft_get_point(char *s, t_point3 *position);
int			ft_get_color(char *s, t_color *color);
void		ft_free(char **aux);

//parser_loads.c
int			ft_load_ambient(t_ambient *ambient, char **s);
int			ft_load_camera(t_camera **camera, char **s);
int			ft_load_light(t_light **light, char **s);

//parser_lists.c
t_lst_obj	*ft_init_obj(void *object, t_obj_type type, double last_dist);
t_lst_obj	*ft_obj_last(t_lst_obj *obj);
void		ft_add_back_obj(t_lst_obj **obj, void **object, t_obj_type type,
				double last_dist);
#endif
