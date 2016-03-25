/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 16:17:27 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>

# include <stdio.h>

# include "libft.h"
# include "mlx.h"

# define EPSILON 0.000001
# define FOV 0.4738147204
# define PI2 6.283185307179587
# define RADIAN 0.01745329251994329
# define MAX_REFLE 5

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4
# define TORUS 5
# define ELLIPSOID 6
# define PARABOLOID 7
# define HYPERBOLOID 8
# define HYPERBOLIC 10
# define ELLIPTIC 11

# define NB_IT 5

# define UNION 1
# define DIFFERENCE 2
# define INTERSECTION 3

typedef struct			s_vector3
{
	double				x;
	double				y;
	double				z;
}						t_vector3;

typedef struct			s_ray
{
	t_vector3			*crd;
	t_vector3			*vec;
	double				intensity;
}						t_ray;

typedef	struct			s_color
{
	double				r;
	double				g;
	double				b;
}						t_color;

typedef struct			s_tex
{
	int					id;
	int					type;
	int					proc_type;
	void				*img;
	char				*data;
	int					width;
	int					height;
	struct s_tex		*next;
}						t_tex;

typedef struct			s_mat
{
	t_color				*color;
	t_tex				*tex;
	int					spec;
	int					id;
	int					refl;
	int					trans;
	double 				ind_trans;
	struct s_mat		*next;
}						t_mat;

typedef struct			s_light
{
	int					id;
	int					type;
	t_vector3			*crd;
	int					intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_obj
{
	int					type;
	int					id;
	t_color				*color;
	t_mat				*mat;
	int					sign;
	t_vector3			*crd;
	double				rx[3];
	double				ry[3];
	double				rz[3];
	double				r;
	double				tan_r;
	double				tan2_r;
	double				pow2_r;
	double				a;
	double				b;
	double				c;
	double				d;
	double				pow2_a;
	double				pow2_b;
	double				pow2_c;
	double				pow2_d;
	double				rt;
	double				pow2_rt;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_interval
{
	double				min;
	double				max;
	t_obj				*obj_max;
	t_obj				*obj_min;
	struct s_interval	*next;
}						t_interval;

typedef struct			s_node
{
	int					type;
	t_obj				*obj;
	struct s_node		*fork1;
	struct s_node		*fork2;
}						t_node;

typedef struct			s_csg
{
	int					id;
	double				scale;
	t_vector3			*crd;
	double				rx[3];
	double				ry[3];
	double				rz[3];
	t_node				*tree;
	struct s_csg		*next;
}						t_csg;

typedef struct			s_hit_pt
{
	int 				hit_obj_id;
	t_vector3			*crd;
	t_vector3			*normal;
	t_ray				*root_ray;
	double 				light_sum;
	t_color				*color;
}						t_hit_pt;

typedef struct			s_cam
{
	t_vector3			*crd;
	double				rx[3];
	double				ry[3];
	double				rz[3];
}						t_cam;

typedef struct			s_menu
{
	int					filter_button;
	int					aa_button;
	char				*text;
	int					selected;
}						t_menu;

typedef struct			s_env
{
	void				*mlx;
	void				*win;

	void				*img;
	char				*addr;
	int					bit;
	int					size;
	int					end;

	void				*img_load;
	char				*addr_load;
	int					bit_load;
	int					size_load;
	int					end_load;

	void				*img_aa;
	char				*addr_aa;

	void				*img_cpy;
	char				*addr_cpy;

	char				*scene_name;
	int					width;
	int					height;

	t_color				*background;
	double				ambient;
	int					aa;
	int					nb_refle;

	int					nb_lights;
	int					nb_rays;

	t_menu				*menu;
	t_cam				*cam;
	t_obj				*obj_lst;
	t_csg				*csg_lst;
	t_light				*light_lst;
	t_mat				*mat_lst;
	t_tex				*tex_lst;
}						t_env;

//init.c
void					init(char *arg, t_env *env);
void					init_mlx(t_env *e);

//parser.c
void					parsing(int fd, t_env *e);

//parsing_func.c
int						xml_cmp(char *str, char *ref);
void					rec_angle(double nbr, double *angle, int deg);
void					rec_cam(int fd, char *ret, t_env *e);
t_mat					*rec_mat(char *str, t_mat *mat_lst);
int						rec_int_value(char *str);
double					rec_double_value(char *str);
t_color					*rec_color(char *str);
t_vector3				*rec_vec(char *str);
char					*rec_name(char *str);
void					rec_rot(char *str, t_obj *obj);
t_tex					*rec_texture(char *str, t_tex *lst_tex);
int						rec_texture_type(char *ret);
void					rec_texture_file(t_tex *tex, char *ret, void *mlx);
void					rec_texture_proc(t_tex *tex, char *ret);

//create_list.c
t_mat					*add_mat(int fd, char *ret, t_mat *mat, t_tex *lst_tex);
t_light					*add_light(int fd, char *ret, t_light *light);
t_obj					*add_obj(int fd, char *ret, t_obj *obj, t_mat *mat);
t_csg					*add_csg(int fd, char *ret, t_env *env);
t_tex					*add_tex(int fd, char *ret, t_tex *tex, void *mlx);

//debug.c
void					debug(t_env *e);

//error.c
void					malloc_error();
void					seg_fault();
void					arg_error();

//raytracer.c
void					cap_color(t_color *color);
void					raytracer(t_env *e, char *addr);

//general_func.c
void					normalise(t_vector3 *vec);

//get_color.c
t_hit_pt				*get_color(t_ray *ray, t_env *e);

//find_intersect.c
t_vector3				*find_intersect(t_ray *ray, t_env *e, t_obj **hit_obj);
void					make_csg_ray(t_ray *ray1, t_ray *ray2, t_csg *csg);

//ray_collision.c
int						ray_collision(t_obj *obj, t_ray *ray, double *k);
int						smallest_k(t_obj *obj, t_ray *ray, double *k);

//is_in_shadow.c
int						is_in_shadow(t_env *env, t_ray *light_ray, \
									t_color *color, t_light *light);

//object_1.c
int						plane(t_obj *obj, t_ray *ray, double *k);
int						sphere(t_obj *obj, t_ray *ray, double *k);
int						cylinder(t_obj *obj, t_ray *ray, double *k);

//object_2.c
int						cone(t_obj *obj, t_ray *ray, double *k);

//object_3.c
int						paraboloid(t_obj *obj, t_ray *ray, double *k);
int						hyperboloid(t_obj *obj, t_ray *ray, double *k);
int						ellipsoid(t_obj *obj, t_ray *ray, double *k);

//rotation.c
void					rotation_matrix(double *absc, double *ord, \
										double angle[3], int neg);
void					csg_rotation(t_vector3 *vec, t_csg *csg, int neg);
void					vector_rotation(t_vector3 *vec, t_obj *obj, int neg);
void					vector_equation(t_obj *obj);

//sub_function.c
int						quadratic_roots(double *deg, double *k);
double					get_dist(t_vector3 *p1, t_vector3 *p2);
void					vec_cpy(t_vector3 *dst, t_vector3 *src);
void					set_vec(t_vector3 *vec, t_vector3 *p1, t_vector3 *p2);
t_vector3				*rot_pt1(t_vector3 *pt1, t_obj *obj);
void					normal_direction(t_vector3 *norm, t_vector3 *vec);
t_vector3				*refle_vec(t_vector3 *normal, t_vector3 *src_vec);
t_vector3				*refre_vec(t_vector3 *normal, t_vector3 *incident, \
									double ind_prev, double ind_next);

//normal.c
void					get_normal(t_vector3 *norm, t_obj *hit_obj, \
									t_vector3 *hit_pt);

//calc_color.c
t_color					*calc_color(t_hit_pt *hit_pt, t_obj *hit_obj, t_env *e);

//reflection.c
void					transparency(t_env *env, t_obj *hit_obj, t_hit_pt *pt);
void					reflection(t_env *env, t_obj *hit_obj, t_hit_pt *pt);

//menu.c
void					print_loading(t_env *e);
void					print_menu(t_env *e);

//post_treatment.c
void					black_and_white(t_env *e);
void					sepia(t_env *e);

//free.c
void					free_ray(t_ray *ray);
void					free_csg(t_csg *csg);
void					free_tree(t_node *tree);
int						free_interval(t_interval *i);
void					free_hit_pt(t_hit_pt *hit_pt);

//free2.c
t_interval				*interval_null(t_interval *i);
int						free_shadow(t_interval *i, t_ray *ray);
void					free_transparency(t_hit_pt *hit_pt, t_ray *ray);

//CSG
t_obj					*ray_collision_csg(t_csg *csg, t_ray *ray, double *k);
t_interval				*intersection_interval(t_interval *i1, t_interval *i2);
t_interval				*difference_interval(t_interval *i1, t_interval *i2);
t_interval				*union_interval(t_interval *i1, t_interval *i2);
t_interval				*get_interval(t_node *node, t_ray *ray);
t_interval				*new_interval(double *k, t_obj *obj);
t_node					*new_node(int type);
t_csg					*new_csg(int id);
t_vector3				*new_point(t_vector3 *pt, t_vector3 *vec, \
									t_vector3 *crd, double k);

#endif
