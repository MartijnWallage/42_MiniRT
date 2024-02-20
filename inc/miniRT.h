/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 17:33:21 by mwallage         ###   ########.fr       */
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
# include <pthread.h>
# include "libft.h"
# include "MLX42.h"

// DEBUGGING FLAGS
# define ANTIALIAS					1
# ifndef BONUS
#  define BONUS 					0
# endif
# define CORES						16
# define CHECK_NORMAL				0
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

typedef enum e_key_mode{
	MODE_CAMERA,
	MODE_OBJECT,
	MODE_SPOT,
}	t_key_mode;

typedef enum e_identifier{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	DISK
}	t_identifier;

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

typedef struct s_spotlight {
	t_vec3				source;
	int					color;
	t_real				diffuse;
	t_real				specular;
	struct s_spotlight	*next;
}	t_spotlight;

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

/// @brief Any object: cylinder, plane, or sphere
typedef struct s_object{
	t_identifier	type;
	t_vec3			center;
	int				color;
	t_vec3			direction;
	t_vec3			up;
	t_real			radius;
	t_real			height;
	t_real			diffuse;
	t_real			shininess;
	struct s_object	*next;
}	t_object;

/// @brief A camera ray or light ray
typedef struct s_ray {
	t_vec3		origin;
	t_vec3		direction;
	t_real		intersection;
	t_vec3		normal;
	t_object	*object;
}	t_ray;

/// @brief The scene after parsing
typedef struct s_scene
{
	t_ambient		ambient;
	t_spotlight		*spotlights;
	t_camera		camera;
	t_object		*objects;
}	t_scene;

/// @brief Main struct that contains everything we need after parsing
typedef struct s_minirt
{
	t_scene			*scene;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_object		*obj_selected;
	t_spotlight		*spotlights_selected;
	t_key_mode		mode;
	int				num;
}	t_minirt;

/// @brief Helper struct during parsing
typedef struct s_build
{
	t_scene		*scene;
	char		**tab;
	char		*line;
	int			fd;
	int			check_ambient;
	int			check_camera;
}	t_build;

/// @brief Helper struct for cylinder calculations
typedef struct s_cyl
{
	t_vec3	nxa;
	t_real	norm_nxa;
	t_vec3	b_x_a;
	t_vec3	b;
	t_real	d_hull;
	t_real	d_cap;
	t_real	t_hull;
	int		orientation_cap;
}	t_cyl;

/// @brief A struct to act as param for multi-threading
typedef struct s_row
{
	t_minirt	*minirt;
	uint32_t	y;
}	t_row;

/*	PARSER	*/
/*	parser.c	*/
void		parse_scene(char **argv, t_build *build);
/*	parser_utils.c		*/
int			ft_countchar(const char *str, char c);
t_real		get_real(t_build *build, const char *str);
int			get_color(t_build *build, char *rgb);
t_vec3		get_vec3(t_build *build, char *numbers);
/*	parse_cylinder.c	*/
t_real		get_radius(t_build *build, char *rad);
void		parse_cyl(t_build *build);
t_vec3		compute_up_vector(t_build *build, t_vec3 direction);
/*	parse_objects.c		*/
void		parse_sphere(t_build *build);
void		parse_plane(t_build *build);
void		parse_disk(t_build *build);
/*	parse_lights.c		*/
void		parse_spotlights(t_build *build);
int			parse_ambient(t_build *build);
/*	parse_camera.c		*/
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

/*	RAYTRACER		*/
/*	compute_bonus.c	*/
void		*init_thread(void *param);
void		multi_thread(void *param);
/*	color utils		*/
int			scale_color(int c, t_real scale);
int			alpha_shade(int c1, int c2, t_real alpha);
int			mix_colors(int color1, int color2);
int			add_colors(int c1, int c2);
/*	compute color	*/
void		compute_specular(int *specular, t_spotlight *spotlight,
				t_ray *camera, t_ray *light);
void		compute_diffuse(int *diffuse, t_spotlight *spotlight, 
				t_ray *camera_ray, t_ray *light_ray);
int			compute_color(t_minirt *minirt, t_ray *camera_ray);
/*	compute ray		*/
t_vec3		get_hitpoint(t_ray *ray);
void		compute_light_ray(t_ray *camera, t_spotlight *spot, t_ray *light);
void		compute_camera_ray(t_minirt *rt, t_real x, t_real y, t_ray *camera);
/*	cylinder utils	*/
t_cyl		init_ints_struct(t_ray	*ray, t_object *cyl);
int			get_min_positive(t_real value0, t_real value1);
int			is_first_visible(t_real a, t_real b, t_real scalar);
t_real		compute_d(t_ray *ray, t_object *cyl,
				t_vec3 cap_center, t_real dot_ray_cyl);
/*	cylinder 		*/
void		compute_cyl_intersection(t_ray *ray, t_object *cyl);
/*	intersections	*/
void		compute_plane_intersection(t_ray *ray, t_object *plane);
void		compute_sphere_intersection(t_ray *ray, t_object *sphere);
void		compute_disk_intersection(t_ray *ray, t_object *disk);
/*	raytracer.c		*/
void		compute_viewport(t_minirt *minirt);
void		compute_ray_object_intersection(t_minirt *minirt, t_ray *ray);
void		raytracer(void *param);

/*	CLEAN		*/
/*	clean.c		*/
void		free_objects(t_object *head);
int			error_msg(const char *info);
void		free_spotlights(t_spotlight *head);
/*	exit.c		*/
void		exit_minirt(t_minirt *minirt, char *message, int status);
void		exit_minirt_build(t_build *build, char *message, int status);
void		protect_malloc(t_build *build, void *check_ptr);

/* GRAPHICS 	*/
/*	hooks.c		*/
void		ft_hook(void *param);
void		ft_mousefunc(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		rotation_hooks(t_minirt *minirt);
void		ft_put_pixel(mlx_image_t *image, unsigned int x,
				unsigned int y, int color);
void		ft_resizefunc(int width, int height, void *param);
/*	translate.c		*/
void		translation_hooks(t_minirt *minirt);
/*	colors.c		*/
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);
/*	set_direction.c	*/
t_vec3		*set_up(t_minirt *minirt);
t_vec3		*set_direction(t_minirt *minirt);

/*	MATH				*/
/*	math_utils.c		*/
t_real		pow2(t_real value);
t_real		ft_abs(t_real value);
t_real		norm2(t_vec3 vector);

/*	vector_utils.c		*/
t_vec3		cross(const t_vec3 a, const t_vec3 b);
t_real		dot(const t_vec3 a, const t_vec3 b);
t_vec3		add(const t_vec3 a, const t_vec3 b);
t_vec3		subtract(const t_vec3 a, const t_vec3 b);
t_vec3		multiply(const t_vec3 a, const t_real scalar);
/*	vector_utils_norm.c	*/
t_real		norm(const t_vec3 vec);
t_vec3		normalize(const t_vec3 vec);

#endif
