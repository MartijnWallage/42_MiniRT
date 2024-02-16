/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 14:24:30 by mwallage         ###   ########.fr       */
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
# define SIZE_ANTIALISING			1

# define MAX_DIGITS_INT_PART 		6
# define MAX_DIGITS_FRAC_PART 		6
# define EPSILON					0.000001
# define TRANSLATION_SPEED 			2
# define ROTATION_SPEED 			0.2
# define ARGUMENT_ERROR				"format: ./miniRT scenes/___.rt"
# define MALLOC_FAILED				"malloc: allocation error"
# define MALLOC_EXITCODE			2
# define PARSING_EXITCODE			3
# define REQUIRE_LIGHT_AND_CAMERA	"parsing error: requires light and camera"
# define CANNOT_OPEN_FILE			"cannot open file"
# define PARSING_ERROR				"parsing error"

# define IMAGE_WIDTH 1000
# define IMAGE_HEIGHT 500

typedef float	t_real;

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

typedef struct s_vec3
{
	t_real	x;
	t_real	y;
	t_real	z;
}	t_vec3;

typedef struct s_ambient {
	t_real		ratio;
	int			color;
}	t_ambient;

typedef struct s_spot {
	t_real		ratio;
	t_vec3		source;
}	t_spot;

typedef struct s_camera{
	t_vec3		viewpoint;
	t_vec3		direction;
	t_real		fov;
	int			tilt;
	t_vec3		corners[2][2];
	t_vec3		up;
	t_vec3		right;
	t_real		width;
	t_real		height;
}	t_camera;

typedef struct s_object{
	t_identifier	type;
	t_vec3			center;
	int				color;
	t_vec3			direction;
	t_vec3			up;
	t_real			radius;
	t_real			height;
	struct s_object	*next;
}	t_object;

typedef struct s_ray {
	t_vec3		origin;
	t_vec3		direction;
	t_real		intersection;
	t_vec3		normal;
	t_object	*object;
}	t_ray;

typedef struct s_scene
{
	t_ambient	ambient;
	t_spot		*spot;
	t_camera	camera;
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
	int			num;
}	t_minirt;

typedef struct s_build
{
	t_scene		*scene;
	char		**tab;
	char		*line;
	int			fd;
	int			check_ambient;
	int			check_camera;
}	t_build;

typedef struct s_cylinder
{
	t_vec3	nxa;
	t_real	norm_nxa;
	t_vec3	b_x_a;
	t_vec3	b;
	t_real	d_hull;
	t_real	d_cap;
	t_real	t_hull;
	int		orientation_cap;
}	t_cylinder;

/*	Cleaner	*/
void		exit_minirt(t_minirt *minirt, char *message, int status);
void		exit_minirt_build(t_build *build, char *message, int status);
void		protect_malloc(t_build *build, void *check_ptr);

/*	Parser	*/
int			ft_countchar(const char *str, char c);
void		parse_scene(char **argv, t_build *build);
t_real		ft_strtod(t_build *build, const char *str);
int			get_color(t_build *build, char *rgb);
t_vec3		get_vec3(t_build *build, char *numbers);
void		parse_sphere(t_build *build);
void		parse_cylinder(t_build *build);
void		parse_plane(t_build *build);
void		parse_spot(t_build *build);
int			parse_ambient(t_build *build);
int			parse_camera(t_build *build);

/*	Checks */
int			is_ratio(t_build *build, char *str);
int			is_angle(t_build *build, char *str);
int			is_posnum(t_build *build, const char *str);
int			is_real(const char *str);
int			is_vector(t_build *build, char *str);
int			is_color(t_build *build, char *str);
int			is_normal_vector(t_build *build, char *str);
int			is_in_range(t_real value, t_real min, t_real max);

/*	RAYTRACER	*/
/*	raytracer.c */
void		raytracer(void *minirt);
void		compute_camera_ray(t_minirt *minirt, t_real x, t_real y, t_ray *ray);
void		compute_ray_object_intersection(t_minirt *minirt, t_ray *ray);
void		compute_light_ray(t_ray *camera_ray, 
				t_spot *spot, t_ray *light_ray);
int			mix_colors(int color1, int color2, float ratio);
int			compute_color(t_minirt *minirt, t_ray *camera_ray);

/*	vector_utils.c	*/
t_vec3		cross(const t_vec3 a, const t_vec3 b);
t_real		dot(const t_vec3 a, const t_vec3 b);
t_vec3		add(const t_vec3 a, const t_vec3 b);
t_vec3		subtract(const t_vec3 a, const t_vec3 b);
t_vec3		multiply(const t_vec3 a, const t_real scalar);
/*	vector_utils_norm.c	*/
t_real		norm(const t_vec3 vec);
t_vec3		normalize(const t_vec3 vec);

/* math_utils.c	*/
t_real		ft_min_positive(t_real value1, t_real value2);
t_real		pow2(t_real value);
t_real		ft_abs(t_real value);
t_real		norm2(t_vec3 vector);

/* intersections.c */
void		compute_plane_intersection(t_ray *ray, t_object *plane);
void		compute_sphere_intersection(t_ray *ray, t_object *sphere);
void		compute_cylinder_intersection(t_ray *ray, t_object *cylinder);
t_cylinder	init_ints_struct(t_ray	*ray, t_object *cylinder);
int			get_min_positive(t_real value1, t_real value2);
t_vec3		get_hitpoint(t_ray *ray);

/* Graphics */
void		ft_hook(void *param);
void		ft_mousefunc(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		rotation_hooks(t_minirt *minirt);
void		ft_put_pixel(mlx_image_t *image, unsigned int x,
				unsigned int y, int color);
void		ft_resizefunc(int width, int height, void *param);

/*	Colors	*/
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

#endif
