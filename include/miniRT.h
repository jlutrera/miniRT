/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:06:47 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/06 19:54:32 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include <math.h>
# include <limits.h>
# include "./errors.h"
# include "./structs.h"

//Windows
# include "../mlx_linux/mlx.h"
# define K_ESC   	0xFF1B

//Mac
//# include <mlx.h>
//# define K_ESC   	53

//Window Size for the image
# define WIDTH 1400
# define ASPECT_RATIO 1.78  //16:9
# define EPSILON 0.000001

//my_hooks.c
void		my_hooks(t_vars *vars);

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
t_point3    vec_to_point(t_vec v);

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
double		compute_shadows(t_scene scene, t_vec p, t_vec n, t_vec d);
double		compute_lighting(t_scene scene, t_vec p, t_vec n, t_vec d);
void		get_closest(t_ray ray, t_lst_obj *obj, t_lst_obj **closest_obj,
				double *t_closest);

//Sphere.c
void		intersect_sphere(t_ray ray, t_sphere *sp, t_point *t);
t_point3	compute_sphere_light(t_sphere *sp, t_scene scene, t_vec p,
				t_ray ray);
t_sphere	*new_sphere(char **s, int *e);
int			ft_load_spheres(t_lst_obj **obj, char **s);

//plane.c
void		intersect_plane(t_ray ray, t_plane *plane, t_point *t);
t_point3	compute_plane_light(t_plane *pl, t_scene scene, t_vec p, t_ray ray);
int			ft_load_planes(t_lst_obj **obj, char **s);
t_plane		*new_plane(char **s, int *e);

//cylinder.c
void		intersect_cylinder(t_ray ray, t_cylinder *cy, t_point *t);

//cylinder2.c
t_point3	compute_cylinder_light(t_cylinder *cy, t_scene scene, t_vec p,
				t_ray ray);
int			ft_load_cylinders(t_lst_obj **obj, char **s);
t_cylinder	*new_cylinder(char **s, int *e);

//parser_utils.c
double		ft_get_dist(void);
int			is_normalized(t_vec vector);
double		ft_atod(char *s);
int			check_comps(char **s, int n);

//parser_gets.c
int			ft_get_vector(char *s, t_vec *direction);
int			ft_get_point(char *s, t_point3 *position);
int			ft_get_color(char *s, t_color *color);

//parser_loads.c
int			ft_load_ambient(t_ambient *ambient, char **s);
int			ft_load_camera(t_camera *camera, char **s);
int			ft_load_light(t_light *light, char **s);

//parser_lists.c
t_lst_obj	*ft_init_obj(void *object, t_obj_type type, double last_dist);
t_lst_obj	*ft_obj_last(t_lst_obj *obj);
void		ft_add_back_obj(t_lst_obj **obj, void **object, t_obj_type type,
				double last_dist);

#endif
