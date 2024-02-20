/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 11:47:50 by mwallage         ###   ########.fr       */
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
# define ANTIALIAS					0
# ifndef BONUS
	# define BONUS 			1
# endif
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
	CYLINDER
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

typedef struct s_ray {
	t_vec3		origin;
	t_vec3		direction;
	t_real		intersection;
	t_vec3		normal;
	t_object	*object;
}	t_ray;

typedef struct s_scene
{
	t_ambient		ambient;
	t_spotlight		*spotlights;
	t_camera		camera;
	t_object		*objects;
}	t_scene;

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

/*	CLEAN		*/
/*	clean.c		*/
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

/*	colors.c	*/
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

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
