/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:21 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 14:41:31 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "../MLX42/MLX42.h"

# define MAX_DIGITS_DOUBLE_INT_PART 6
# define MAX_DIGITS_DOUBLE_FRAC_PART 2
# define MAX_LEN_DOUBLE (MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 1)
# define MIN_color	0
# define MAX_color	255
# define EPSILON	0.000001

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

typedef struct s_light{
	t_identifier	type;
	double			ratio;
	double			color[3];
	double			source[3];
}	t_light;

typedef struct s_camera{
	double	viewpoint[3];
	double	normvect[3];
	int		fov;
}	t_camera;

typedef struct s_object{
	t_identifier	type;
	double			center[3];
	unsigned char	color[3];
	double			normvect[3];
	double			diameter;
	double			height;
}	t_object;

typedef struct s_scene{
	t_light		*ambient;
	t_light		**spots;
	t_camera	*camera;
	t_object	**objects;
}	t_scene;

typedef struct s_mini_rt{
	t_scene		*scene;
	mlx_t		*mlx;
	mlx_image_t	*image;
} t_mini_rt;

/*	Initialisation and clean up handling */
# define ARGUMENT_ERROR	"Wrong number of arguments. Expected a file name\n"
# define MALLOC_FAILED	"Malloc: Allocation error"


/*	cleaner*/
void	exit_minirt(t_scene *scene, char *message, int status);
void	free_tab(void **tab);

/*	Parser	*/
# define REQUIRE_LIGHT_AND_CAMERA	"Parsing error: Requires light and camera\n"
# define CANNOT_OPEN_FILE			"Parsing error: Cannot open file\n"
# define PARSING_ERROR				"Parsing error"

int		get_str_array_len(char **chars);
void	free_str_array(char **chars);
void	parse_scene(char **argv, t_scene *scene);

void	str_to_vector(double dest[3], char *str);
double	ft_strtod(char *str);

int		is_numstr(const char *str);
int		is_valid_double(const char *str);
int		is_rbg(double color[3]);
int 	is_vector(char *str);
int		is_normal(double vector[3]);

/* Graphics and displaying */
void	ft_hook(void *param);
void	put_circle(mlx_image_t* image);
/* Prints for debugging */
void	print_scene(t_scene *scene);

#endif
