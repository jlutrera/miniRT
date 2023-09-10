/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:49:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/02/09 09:49:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void rotate_plane(void *mlx, void *window, double angle)
{
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);

    int center_x = WIDTH * 0.6 / 2;
    int center_y = HEIGHT * 0.6 / 2;

    for (int x = 0; x < WIDTH * 0.6; x++)
    {
        for (int y = 0; y < HEIGHT * 0.6; y++)
        {
            int new_x = (x - center_x) * cos_angle - (y - center_y) * sin_angle + center_x;
            int new_y = (x - center_x) * sin_angle + (y - center_y) * cos_angle + center_y;

            if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT)
            {
                int plane_color = mlx_get_color_value(mlx, 0xFFFFFF); // Color blanco
                mlx_pixel_put(mlx, window, new_x, new_y, plane_color);
            }
        }
    }
}

void draw_plane(t_vars *vars)
{
    int x, y;
    int plane_color = 0xFFFFFF; // Color blanco (formato RGB)

    for (x = 0; x < WIDTH * 0.6; x++)
    {
        for (y = 0; y < HEIGHT * 0.6; y++)
        {
            mlx_pixel_put(vars->mlx, vars->win, x, y, plane_color);
        }
    }
}

void draw_sphere_with_highlight(t_vars *window, int x, int y, int radius, int color, float light_direction[3]) {
    // Dividir la esfera en círculos y dibujarlos
    for (int z = -radius; z <= radius; z++) {
        int circle_radius = (int)sqrt(radius * radius - z * z);

        for (int i = x - circle_radius; i <= x + circle_radius; i++) {
            for (int j = y - circle_radius; j <= y + circle_radius; j++) {
                if ((i - x) * (i - x) + (j - y) * (j - y) <= circle_radius * circle_radius) {
                    // Calcula el vector normal
                    float normal[3] = {i - x, j - y, z};

                    // Normaliza el vector normal
                    float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
                    normal[0] /= length;
                    normal[1] /= length;
                    normal[2] /= length;

                    // Calcula el coseno del ángulo entre la luz y la normal
                    float cos_angle = normal[0] * light_direction[0] + normal[1] * light_direction[1] + normal[2] * light_direction[2];

                    // Ajusta la intensidad del color en función del ángulo
                    int pixel_color = color;
                    if (cos_angle > 0.5) {
                        // Aumenta la intensidad del color
                        pixel_color = 0xFFFFFF; // Color blanco brillante
                    }

                    mlx_pixel_put(window->mlx, window->win, i, j, pixel_color);
                }
            }
        }
    }
}

void draw_sphere(t_vars *window, int x, int y, int radius, int color) {
	 int i, j;
    // Dividir la esfera en círculos y dibujarlos
    for (int z = -radius; z <= radius; z++) {
        int circle_radius = (int)sqrt(radius * radius - z * z);
    	for (i = x - circle_radius; i <= x + circle_radius; i++) {
        	for (j = y - circle_radius; j <= y + circle_radius; j++) {
           		if ((i - x) * (i - x) + (j - y) * (j - y) <= circle_radius * circle_radius) {
                	mlx_pixel_put(window->mlx, window->win, i, j, color); // Color blanco
            	}
        	}
    	}
    }
}

void	process_img(t_scene scene)
{
	t_vars	vars;
	int sphere_x = WIDTH / 2;
    int sphere_y = HEIGHT / 2;
    int sphere_radius = 50;
	int sphere_color = 0xFF00;

	t_point3d rayOrigin = {1, 0, 0};
    t_point3d rayDirection = {0, -0.5, -0.5};
	float lightDirection[3] = {0, -0.5, -0.5};

    t_sphere sphere = {{0, 0, -5}, 50.0, {255,0,0}};
    float t;

    if (intersectRaySphere(rayOrigin, rayDirection, sphere, &t)) {
        printf("Intersección en t = %f\n", t);
    } else {
        printf("No hay intersección.\n");
    }
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, name);
   // draw_sphere(&vars, sphere_x, sphere_y, sphere_radius, sphere_color);
	draw_sphere_with_highlight(&vars, sphere_x, sphere_y, sphere_radius, sphere_color, lightDirection),
	draw_plane(&vars);
	rotate_plane(vars.mlx, vars.win, 3.14 / 6); // Rotar 30 grados (pi/6 radianes) en sentido horario
	
	my_hooks(&vars);
	mlx_loop(vars.mlx);
}
