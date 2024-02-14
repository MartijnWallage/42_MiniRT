/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 13:56:45 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"
# include "MLX42.h"

// DEBUGGING FLAGS
# define CHECK_PARSING_NORMAL 		0

# define MAX_DIGITS_INT_PART 		6
# define MAX_DIGITS_FRAC_PART 		6
# define MAX_LEN_DOUBLE (MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 1)
# define MIN_color					0
# define MAX_color					255
# define EPSILON					0.000001
# define TRANSLATION_SPEED 			1
# define ROTATION_SPEED 			0.2
# define ARGUMENT_ERROR				"Wrong number of arguments. Expected a file name"
# define MALLOC_FAILED				"Malloc: Allocation error"
# define MALLOC_EXITCODE			2
# define PARSING_EXITCODE			3
# define REQUIRE_LIGHT_AND_CAMERA	"Parsing error: Requires light and camera"
# define CANNOT_OPEN_FILE			"Parsing error: Cannot open file"
# define PARSING_ERROR				"Parsing error"

# define IMAGE_WIDTH 1200
# define IMAGE_HEIGHT 800

typedef enum e_identifier{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_identifier;

typedef enum e_key_mode{
	MODE_CAMERA,
	MODE_OBJECT,
	MODE_SPOT,
}	t_key_mode;

typedef struct s_vec3 {
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_ambient {
	double			ratio;
	int				color;
}	t_ambient;

typedef struct s_spot {
	double			ratio;
	t_vec3			source;
}	t_spot;

typedef struct s_camera{
	t_vec3		viewpoint;
	t_vec3		direction;
	double		fov;
	int			tilt;
	t_vec3		corners[2][2];
	t_vec3		up;
	t_vec3		right;
	double		width;
	double		height;
}	t_camera;

typedef struct s_object{
	t_identifier	type;
	t_vec3			center;
	int				color;
	t_vec3			direction;
	t_vec3			up;
	double			radius;
	double			height;
	struct s_object	*next;
}	t_object;

typedef struct s_ray {
	t_vec3		origin;
	t_vec3		direction;
	double		intersection;
	t_vec3		normal;
	t_object	*object;
} t_ray;

typedef struct s_scene
{
	t_ambient	*ambient;
	t_spot		*spot;
	t_camera	*camera;
	t_object	*objects;
}	t_scene;

typedef struct s_minirt
{
	t_scene		*scene;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_object	*obj_selected;
	t_spot		*spot_selected;
	t_key_mode	mode;
}	t_minirt;

/*	Cleaner	*/
void	exit_minirt(t_scene *scene, char *message, int status);
void	free_tab(void **tab);
void	protect_malloc(t_scene *scene, void *free_ptr, void *check_ptr);
// void	protect_malloc(t_minirt *minirt, void *check_ptr);

/*	Parser	*/
int		tablen(void **tab);
int		ft_countchar(const char *str, char c);
void	parse_scene(char **argv, t_scene *scene);
double	ft_strtod(const char *str);
int		get_color(t_scene *scene, char *rgb);
t_vec3	get_vec3(t_scene *scene, char *numbers);
int		parse_sphere(t_scene *scene, char **columns);
int		parse_cylinder(t_scene *scene, char **columns);
int		parse_plane(t_scene *scene, char **columns);
int		parse_spot(t_scene *scene, char **columns);
int		parse_ambient(t_scene *scene, char **columns);
int		parse_camera(t_scene *scene, char **columns);

/*	Checks */
int		is_ratio(char *str);
int		is_angle(char *str);
int		is_posnum(const char *str);
int		is_double(const char *str);
int 	is_vector(char *str);
int		is_normal_vector(char *str);
int		is_color_vector(char *str);
int		is_in_range(double value, double min, double max);

/*	RAYTRACER	*/
/*	raytracer.c */
void	raytracer(void *minirt);
void	compute_camera_ray(t_minirt *minirt, int x, int y, t_ray *ray);
void	compute_ray_object_intersection(t_minirt *minirt, t_ray *ray);

/*	vector_utils.c	*/
double	angle(const t_vec3 a, const t_vec3 b);
t_vec3	cross(const t_vec3 a, const t_vec3 b);
double	dot(const t_vec3 a, const t_vec3 b);
t_vec3	add(const t_vec3 a, const t_vec3 b);
t_vec3	subtract(const t_vec3 a, const t_vec3 b);
t_vec3	multiply(const t_vec3 a, const double scalar);
double	norm(const t_vec3 vec);
t_vec3	normalize(const t_vec3 vec);

/* math_utils.c	*/
double	ft_min_positive(double value1, double value2);
double	pow2(double value);
double	ft_abs(double value);

/* intersections.c */
void	calc_plane_intersection(t_ray *ray, t_object *plane);
void	calc_sphere_intersection(t_ray *ray, t_object *sphere);
void	calc_cylinder_intersection(t_ray *ray, t_object *cylinder);

/* Graphics */
void	ft_hook(void *param);
void	ft_resize(int width, int height, void *params);
void 	ft_mousefunc(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void	rotation_hooks(t_minirt *minirt);
void    ft_put_pixel(mlx_image_t* image, unsigned int x, unsigned int y, int color);
void	ft_resizefunc(int width, int height, void *param);

/*	Colors	*/
int 	get_rgba(int r, int g, int b, int a);
int 	get_r(int rgba);
int 	get_g(int rgba);
int 	get_b(int rgba);
int 	get_a(int rgba);

/*	TEST 	*/
void	print_scene(t_scene *scene);

#endif
