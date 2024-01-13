#ifndef MINI_RT_H
# define MINI_RT_H

enum	identifier{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

typedef struct	s_light{
	identifier	type;
	float		ratio;
	float		colour[3];
	float		source[3];
}	t_light;


typedef struct	s_camera{
	float	viewpoint[3];
	float	normvect[3];
	int		fov;
}	t_camera;

typedef struct	s_object{
	identifier		type;
	float			center[3];
	unsigned char	colour[3];
	float			norm_vector[3];
	float			diameter;
	float			height;
}	t_object;

typedef struct	s_scene{
	t_light		ambient;
	t_light		*spots;
	t_camera	camera;
	t_object	*objects;
}	t_scene;

#endif