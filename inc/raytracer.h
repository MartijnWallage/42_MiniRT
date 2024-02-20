#include "miniRT.h"

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

/*	color utils		*/
int		scale_color(int c, t_real scale);
int 	alpha_shade(int c1, int c2, t_real alpha);
int		mix_colors(int color1, int color2);
int 	add_colors(int c1, int c2);
/*	compute color	*/
int		compute_color(t_minirt *minirt, t_ray *camera_ray);
/*	compute ray		*/
t_vec3	get_hitpoint(t_ray *ray);
void	compute_light_ray(t_ray *camera_ray, t_spotlight *spot, t_ray *light_ray);
void	compute_camera_ray(t_minirt *minirt, t_real x, t_real y, t_ray *ray);
/*	cylinder utils	*/
t_cyl	init_ints_struct(t_ray	*ray, t_object *cyl);
int		get_min_positive(t_real value0, t_real value1);
int		is_first_visible(t_real a, t_real b, t_real scalar);
/*	cylinder 		*/
void	compute_cyl_intersection(t_ray *ray, t_object *cyl);
void	compute_plane_intersection(t_ray *ray, t_object *plane)
/*	intersections	*/
void	compute_plane_intersection(t_ray *ray, t_object *plane);
void	compute_sphere_intersection(t_ray *ray, t_object *sphere);
void	compute_cyl_intersection(t_ray *ray, t_object *cyl);
/*	raytracer		*/
void	raytracer(void *param);
void	compute_ray_object_intersection(t_minirt *minirt, t_ray *ray);