/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/17 19:27:03 by mwallage         ###   ########.fr       */
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

# define MAX_DIGITS_DOUBLE_INT_PART 6
# define MAX_DIGITS_DOUBLE_FRAC_PART 2
# define MAX_LEN_DOUBLE (MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 1)
# define MIN_color	0.0
# define MAX_color	255.0
# define EPSILON	0.000001
# define ARGUMENT_ERROR	"Wrong number of arguments. Expected a file name"
# define MALLOC_FAILED	"Malloc: Allocation error"
# define MALLOC_EXITCODE	2
# define PARSING_EXITCODE	3
# define REQUIRE_LIGHT_AND_CAMERA	"Parsing error: Requires light and camera"
# define CANNOT_OPEN_FILE			"Parsing error: Cannot open file"
# define PARSING_ERROR				"Parsing error"

typedef enum e_identifier{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_identifier;

typedef double			t_vector[3];
typedef unsigned char	t_color[3];

typedef struct s_ambient {
	double			ratio;
	t_color			color;
	t_vector		source;
}	t_ambient;

typedef struct s_spot {
	double			ratio;
	t_color			color;
	t_vector		source;
	struct s_spot	*next;
}	t_spot;

typedef struct s_camera{
	t_vector		viewpoint;
	t_vector		normvect;
	unsigned char	fov;
}	t_camera;

typedef struct s_object{
	t_identifier	type;
	t_vector		center;
	t_color			color;
	t_vector		normvect;
	double			diameter;
	double			height;
	struct s_object	*next;
}	t_object;

typedef struct s_scene{
	t_ambient	*ambient;
	t_spot		*spots;
	t_camera	*camera;
	t_object	*objects;
}	t_scene;

/*	cleaner*/
void		free_tab(void **tab);
void		exit_minirt(t_scene *scene, char *message, int status);
void		protect_malloc(t_scene *scene, void *free_ptr, void *check_ptr);
/*	Parser	*/
int			tablen(void **tab);
void		parse_scene(char **argv, t_scene *scene);
void		str_to_vector(double dest[3], char *str);
double		ft_strtod(char *str);
void		get_color(t_color color, char *rgb);
void		get_vector(t_vector vect, char *numbers);
void		parse_sphere(t_scene *scene, char **columns);
void		parse_cylinder(t_scene *scene, char **columns);
void		parse_plane(t_scene *scene, char **columns);
void		parse_spot(t_scene *scene, char **columns);
void		parse_ambient(t_scene *scene, char **columns);
void		parse_camera(t_scene *scene, char **columns);
/*	Checks */
int			is_numstr(const char *str);
int			is_valid_double(const char *str);
int			is_rbg(t_color color);
//int 		is_vector(char *str);
int			is_normal(double vector[3]);

#endif
