#include "miniRT.h"

typedef struct s_build
{
	t_scene		*scene;
	char		**tab;
	char		*line;
	int			fd;
	int			check_ambient;
	int			check_camera;
}	t_build;

/*	Parser	*/
int			ft_countchar(const char *str, char c);
void		parse_scene(char **argv, t_build *build);
t_real		get_real(t_build *build, const char *str);
int			get_color(t_build *build, char *rgb);
t_vec3		get_vec3(t_build *build, char *numbers);
void		parse_sphere(t_build *build);
void		parse_cyl(t_build *build);
void		parse_plane(t_build *build);
void		parse_spotlights(t_build *build);
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