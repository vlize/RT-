/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 10:55:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/14 09:29:08 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void print_obj(t_obj *obj)
{
  t_obj *start;

  start = obj;
  printf("OBJET\n");
  while (obj)
  {
    printf("id: %d\n", obj->id);
    printf("type: %d\n", obj->type);
    printf("color: r:%f g:%f b:%f\n", obj->mat->color->r, obj->mat->color->g, obj->mat->color->b);
    printf("crd: x:%f y:%f z:%f\n", obj->crd->x, obj->crd->y, obj->crd->z);
    printf("material: %d\n", obj->mat->id);
    printf("\n");
    obj = obj->next;
  }
  obj = start;
}

static void print_mat(t_mat *mat)
{
  t_mat *start;

  start = mat;
  printf("MAT\n");
  while (mat)
  {
    printf("id: %d\n", mat->id);
    printf("spec: %d\n", mat->spec);
    printf("color: r:%f g:%f b:%f\n", mat->color->r, mat->color->g, mat->color->b);
    printf("\n");
    mat = mat->next;
  }
  mat = start;
}

static void print_light(t_light *light)
{
  t_light *start;

  start = light;
  printf("LIGHT\n");
  while (light)
  {
    printf("id: %d\n", light->id);
    printf("crd: x:%f y:%f z:%f\n", light->crd->x, light->crd->y, light->crd->z);
    printf("\n");
    light = light->next;
  }
  light = start;
}

static void print_env(t_env *e)
{
  printf("ENV\n");
  printf("scene name:%s\n", e->scene_name);
  printf("width: %d height: %d\n", e->width, e->height);
  printf("background: r:%f g:%f b:%f\n", e->background->r, e->background->g, e->background->b);
  printf("ambient: %f\n", e->ambient);
  printf("aa: %d\n", e->aa);
  printf("\n");
}

static void print_cam(t_env *e)
{
  printf("CAM\n");
  printf("crd: x:%f y:%f z:%f\n", e->cam->crd->x, e->cam->crd->y, e->cam->crd->z);
  printf("\n");
}

void debug(t_env *e)
{
  print_obj(e->obj_lst);
  print_mat(e->mat_lst);
  print_light(e->light_lst);
  print_env(e);
  print_cam(e);
}
