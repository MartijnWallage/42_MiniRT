# 42_MiniRT
Authors: Thomas Höfting (thofting), Martijn Wallage (mwallage)

## Components

1.	Parsing

Scene description in a file.rt

Ambient lightning:
`A 0.2 255,255,255`

Camera:
`C -50,0,0,20	0,0,1	70`

Light:
`L	-40.0,50.0,0.0	0.6	10,0,255`

Sphere:
`sp	0.0,0.0,20.6	12.6	10,0,255`

Plane:
`pl	0.0,0.0,-10.0	0.0,1.0,0.0	0,0,255`

Cylinder:
`cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255`

2.	Modelling

t_identifier	enum {
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

typedef struct	s_light {
	t_identifier	type;
	float		ratio;
	float[3]	color;
	float[3]	source;
}	t_light;


typedef struct	s_camera	{
	float[3]	viewpoint;
	float[3]	normvect;
	int			FOV;
}	t_camera;

typedef struct	s_object {
	t_identifier		type;
	float[3]			center;
	unsigned char[3]	color;
	float[3]			normvect;
	float				diameter;
	float				height;
}	t_object;

typedef struct	s_scene {
	t_light		ambient;
	t_light		*spots;
	t_camera	camera;
	t_objects	*objects;
}

### Methods

calculate surfaces

calculate rays on the basis of camera

calculate intersections of ray with surface

calculate rays from the spotlight

calculate shadows

calculate color of intersections based on lighting and shadows

calculate translations and rotations

3.	Image processing

For each ray write one pixel to an image.

Display the image to the screen.

Take care of resizing etc.