/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/20 14:44:28 by mwallage         ###   ########.fr       */
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

# define MAX_DIGITS_DOUBLE_INT_PART 6
# define MAX_DIGITS_DOUBLE_FRAC_PART 2
# define MAX_LEN_DOUBLE (MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 1)
# define MIN_color	0
# define MAX_color	255
# define EPSILON	0.000001
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

typedef double			t_vector[3];

typedef struct s_ambient {
	double			ratio;
	int				color;
	t_vector		source;
}	t_ambient;

typedef struct s_spot {
	double			ratio;
	int				color;
	t_vector		source;
	struct s_spot	*next;
}	t_spot;

typedef struct s_camera{
	t_vector		viewpoint;
	t_vector		normvect;
	double			fov;
	int				tilt;
	t_vector		corners[2][2];
	t_vector		up;
	t_vector		right;
	double			width;
	double			height;
}	t_camera;

typedef struct s_object{
	t_identifier	type;
	t_vector		center;
	int				color;
	t_vector		normvect;
	double			diameter;
	double			height;
	struct s_object	*next;
}	t_object;

typedef struct s_ray {
	t_vector	normvect;
	double		intersection;
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
} t_minirt;

/*	Cleaner	*/
void	exit_minirt(t_scene *scene, char *message, int status);
void	free_tab(void **tab);
void	protect_malloc(t_scene *scene, void *free_ptr, void *check_ptr);

/*	Parser	*/
int			tablen(void **tab);
void		parse_scene(char **argv, t_scene *scene);
double		ft_strtod(char *str);
int			get_color(t_scene *scene, char *rgb);
void		get_vector(t_scene *scene, t_vector vect, char *numbers);
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

void	raytracer(t_minirt *minirt);
/*	vector_utils.c	*/
double	angle(const t_vector a, const t_vector b);
void	cross(const t_vector a, const t_vector b, t_vector result);
double	dot(const t_vector a, const t_vector b);
void	add(const t_vector a, const t_vector b, t_vector result);
void	subtract(const t_vector a, const t_vector b, t_vector result);
void	multiply(const t_vector a, const double scalar, t_vector result);
double	norm(const t_vector vec);
void	normalize(const t_vector vec, t_vector result);
/* Graphics */
void	ft_hook(void *param);
void	put_circle(mlx_image_t* image);
/*	Colors	*/
int 	get_rgba(int r, int g, int b, int a);
int 	get_r(int rgba);
int 	get_g(int rgba);
int 	get_b(int rgba);
int 	get_a(int rgba);

/*	TEST 	*/
void	print_scene(t_scene *scene);

#endif
