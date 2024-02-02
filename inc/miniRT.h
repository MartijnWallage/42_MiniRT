/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/25 17:03:48 by mwallage         ###   ########.fr       */
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
# include "libft.h"
# include "MLX42.h"

# define ACTIVATE_COLOR 1

# define MAX_DIGITS_DOUBLE_INT_PART 6
# define MAX_DIGITS_DOUBLE_FRAC_PART 2
# define MAX_LEN_DOUBLE (MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 1)
# define MIN_color	0
# define MAX_color	255
# define EPSILON	0.000001
# define TRANSLATION_SPEED 1
# define ROTATION_SPEED 0.2
# define ARGUMENT_ERROR	"Wrong number of arguments. Expected a file name"
# define MALLOC_FAILED	"Malloc: Allocation error"
# define MALLOC_EXITCODE	2
# define PARSING_EXITCODE	3
# define REQUIRE_LIGHT_AND_CAMERA	"Parsing error: Requires light and camera"
# define CANNOT_OPEN_FILE			"Parsing error: Cannot open file"
# define PARSING_ERROR				"Parsing error"

# define IMAGE_WIDTH 1000
# define IMAGE_HEIGHT 500

typedef enum e_identifier{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_identifier;

typedef struct s_vec3 {
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_ambient {
	double			ratio;
	int				color;
	t_vec3			source;
}	t_ambient;

typedef struct s_spot {
	double			ratio;
	int				color;
	t_vec3			source;
	struct s_spot	*next;
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
	double			radius;
	double			height;
	struct s_object	*next;
}	t_object;

typedef struct s_ray {
	t_vec3		origin;
	t_vec3		direction;
	double		intersection;
	t_vec3		normal;			// surface normal for shading
	t_object	*object;
} t_ray;

typedef struct s_scene{
	t_ambient	*ambient;
	t_spot		*spots;
	t_camera	*camera;
	t_object	*objects;
}	t_scene;

typedef struct s_minirt{
	t_scene		*scene;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_object	*selected;
} t_minirt;

/*	Cleaner	*/
void	exit_minirt(t_scene *scene, char *message, int status);
void	free_tab(void **tab);
void	protect_malloc(t_scene *scene, void *free_ptr, void *check_ptr);
// void	protect_malloc(t_minirt *minirt, void *check_ptr);
/*	Parser	*/
int			tablen(void **tab);
void		parse_scene(char **argv, t_scene *scene);
double		ft_strtod(char *str);
int			get_color(t_scene *scene, char *rgb);
t_vec3		get_vec3(t_scene *scene, char *numbers);
void		parse_sphere(t_scene *scene, char **columns);
void		parse_cylinder(t_scene *scene, char **columns);
void		parse_plane(t_scene *scene, char **columns);
void		parse_spot(t_scene *scene, char **columns);
void		parse_ambient(t_scene *scene, char **columns);
void		parse_camera(t_scene *scene, char **columns);
/*	Checks */
int			is_numstr(const char *str);
int			is_valid_double(const char *str);
// int			is_rbg(int color);
//int 		is_vector(char *str);
int			is_normal(double vector[3]);

/*	RAYTRACER	*/
/*	raytracer.c */
void	raytracer(void *minirt);

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

/* intersections.c */
void	calc_plane_intersection(t_ray *ray, t_object *plane);
void	calc_sphere_intersection(t_ray *ray, t_object *sphere);
void	calc_cylinder_intersection(t_ray *ray, t_object *cylinder);

/* Graphics */
void	ft_hook(void *param);
void	put_circle(mlx_image_t* image);

t_vec3	rotate_x_axis(t_vec3 vector, double alpha);
t_vec3	rotate_y_axis(t_vec3 vector, double alpha);
t_vec3	rotate_z_axis(t_vec3 vector, double alpha);

/*	Colors	*/
int 	get_rgba(int r, int g, int b, int a);
int 	get_r(int rgba);
int 	get_g(int rgba);
int 	get_b(int rgba);
int 	get_a(int rgba);

/*	TEST 	*/
void	print_scene(t_scene *scene);

#endif
