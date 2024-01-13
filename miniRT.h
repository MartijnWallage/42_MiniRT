#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "include/libft/libft.h"
# include <math.h>

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
	float			ratio;
	float			colour[3];
	float			source[3];
}	t_light;

typedef struct s_camera{
	float	viewpoint[3];
	float	normvect[3];
	int		fov;
}	t_camera;

typedef struct s_object{
	t_identifier	type;
	float			center[3];
	unsigned char	colour[3];
	float			norm_vector[3];
	float			diameter;
	float			height;
}	t_object;

typedef struct s_scene{
	t_light		*ambient;
	t_light		**spots;
	t_camera	*camera;
	t_object	**objects;
}	t_scene;

/*	Initialisation and clean up handling */
# define ARGUMENT_ERROR "Wrong number of arguments. Expected a file name\n"
# define MALLOC_FAILED "Malloc: Allocation error"

void	exit_mini_rt(t_scene *scene, char *message, int status);

/*	Parsing	*/
# define REQUIRE_LIGHT_AND_CAMERA "Parsing error: Requires light and camera\n"
# define CANNOT_OPEN_FILE "Parsing error: Cannot open file\n"
# define PARSING_ERROR "Parsing error"

int		get_str_array_len(char **chars);
void	free_str_array(char **chars);
void	parse_scene(char **argv, t_scene *scene);

#endif