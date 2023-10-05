#include "../include/miniRT.h"

double	intersect_disk(t_ray ray, t_vec center, t_vec normal, double radius)
{
	double denom;
	double t;

	denom = vec_dot(normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return INFINITY; // Rayo paralelo al disco
	t = vec_dot(vec_sub(center, vec(ray.origin.x, ray.origin.y, ray.origin.z)), normal) / denom;
	if (t < EPSILON) 
		return INFINITY; // Disco detrás del rayo
	t_vec P = vec_add(vec(ray.origin.x, ray.origin.y, ray.origin.z), vec_mul(ray.dir, t)); // Punto de intersección con el plano del disco
	if (vec_length(vec_sub(P, center)) > radius)
		return INFINITY; // Punto fuera del disco
	return t;
}

void intersect_cylinder(t_ray ray, t_cylinder *cy, t_point *t)
{
	t_vec OD = ray.dir;
	t_vec CD = vec_unit(cy->direction); // Asegúrate de que este vector esté normalizado
	
	double radius = cy->radius; // Asegúrate de que este es el radio, no el diámetro
	
	t_vec OC = vec_sub(vec(ray.origin.x, ray.origin.y, ray.origin.z), vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z));
	t_vec OC_perp = vec_sub(OC, vec_mul(CD, vec_dot(OC, CD)));
	t_vec OD_perp = vec_sub(OD, vec_mul(CD, vec_dot(OD, CD)));

	if (vec_length(OD_perp) < EPSILON) 
    	OD_perp = vec(0,0,1); // O cualquier otro vector que sea perpendicular a CD
	
	double a = vec_dot(OD_perp, OD_perp);
	double b = 2 * vec_dot(OC_perp, OD_perp);
	double c = vec_dot(OC_perp, OC_perp) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	//No hay intersección
	if (discriminant < EPSILON)
	{
		*t = (t_point){INFINITY, INFINITY};
		return;
	}
	
	double sqrt_discriminant = sqrt(discriminant);
	double t1 = (-b + sqrt_discriminant) / (2 * a);
	double t2 = (-b - sqrt_discriminant) / (2 * a);

	// Calcula los puntos de intersección P1 y P2 con las paredes laterales del cilindro
	t_vec P1 = vec_add(vec(ray.origin.x, ray.origin.y, ray.origin.z), vec_mul(ray.dir, t1));
	t_vec P2 = vec_add(vec(ray.origin.x, ray.origin.y, ray.origin.z), vec_mul(ray.dir, t2));

	// Calcula las distancias h1 y h2 desde los puntos de intersección hasta los centros de las bases del cilindro
	double h1 = vec_dot(vec_sub(P1, vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z)), CD);
	double h2 = vec_dot(vec_sub(P2, vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z)), CD);

	//t está dentro de los límites del cilindro
	if (h1 < 0 || h1 > cy->height)
		t1 = INFINITY;
	if (h2 < 0 || h2 > cy->height)
		t2 = INFINITY;
	
	// Calcula las intersecciones con las bases del cilindro
	double t_base1 = intersect_disk(ray, vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z), CD, radius);
	double t_base2 = intersect_disk(ray, vec_add(vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z), vec_mul(CD, cy->height)), CD, radius);
	
	//calculo el valor más pequeño de los cuatro obtenidos
	double t_values[4] = {t1, t2, t_base1, t_base2};
	double t_min = INFINITY;
	for(int i = 0; i < 4; i++)
	{
		if (t_values[i] > EPSILON && t_values[i] < t_min)
			t_min = t_values[i];
	}
	*t = (t_point){t_min, INFINITY};
}

// t_point3	compute_cylinder_light(t_cylinder *cy, t_scene scene, t_vec P, t_ray ray)
// {
// 	t_vec 		N;
// 	double 		i;
// 	double		h;
// 	double		r;

// 	h = vec_dot(vec_sub(P, vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z)), cy->direction);
// 	if (fabs(h - cy->height) <= EPSILON || fabs(h) <= EPSILON)
// 		r = P.z - cy->coordinate.z;
// 	else 
// 		r = cy->height * h / fabs(h) + cy->coordinate.z;
// 	N = vec_unit(vec( P.x - cy->coordinate.x, P.y - cy->coordinate.y, r));
// 	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1));
// 	i += compute_shadows(scene, P, N, vec_mul(ray.dir, -1));
// 	return (t_point3){cy->color.r * i, cy->color.g * i, cy->color.b * i};
// }

t_point3	compute_cylinder_light(t_cylinder *cy, t_scene scene, t_vec P, t_ray ray)
{
	t_vec 		N;
	double 		i;
	double		h;

	h = vec_dot(vec_sub(P, vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z)), cy->direction);
	if (fabs(h - cy->height) <= EPSILON)
		N = vec_unit(cy->direction); // Normal para la base superior
	else if (fabs(h) <= EPSILON)
		N = vec_unit(vec_mul(cy->direction, -1)); // Normal para la base inferior
	else 
	{
		// Cálculo de la normal para el lateral del cilindro
		t_vec CP = vec_unit(vec_sub(P, vec(cy->coordinate.x, cy->coordinate.y, cy->coordinate.z)));
		t_vec proj = vec_mul(cy->direction, vec_dot(CP, cy->direction));
		N = vec_unit(vec_sub(CP, proj));
	}
	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1));
	i += compute_shadows(scene, P, N, vec_mul(ray.dir, -1));
	return (t_point3){cy->color.r * i, cy->color.g * i, cy->color.b * i};
}

int ft_load_cylinders(t_lst_obj **obj, char **s)
{
	int			e;
	t_cylinder	*new_cy;

	if (check_comps(s, 6))
		return NUM_COMPONENTS_E;
	new_cy = new_cylinder(s, &e);
	if (!new_cy)
		return e;
	ft_add_back_obj(obj, (void**) &new_cy, CYLINDER, ft_get_dist());
	return SUCCESS;
}

t_cylinder	*new_cylinder(char **s, int *e)
{
	t_cylinder	*new_cy;

	new_cy = ft_calloc(sizeof(t_cylinder *), 1);
	if (!new_cy)
	{
		*e = MEMORY_E;
		return NULL;
	}
	*e = SUCCESS;
	new_cy->radius = ft_atod(s[3]) / 2;
	new_cy->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cy->coordinate) == -1 ||
		ft_get_vector(s[2], &new_cy->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_cy->direction))
		*e = NORM_VECTOR_E;
	else if (new_cy->radius <= 0 || new_cy->height <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[5], &new_cy->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_cy);
	return free(new_cy), NULL;
}
