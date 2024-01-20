/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:04:25 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/19 14:16:40 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_scene(t_scene *scene)
{
	printf("\n***PARSING**************\n");
	printf("\nCAMERA:\n");
	printf("Fov: \t\t%f\n", scene->camera->fov);
	printf("Viewpoint: %lf, %lf, %lf\n",
		scene->camera->viewpoint[0],
		scene->camera->viewpoint[1], 
		scene->camera->viewpoint[2]);
	printf("Norm vector: %lf, %lf, %lf\n",
		scene->camera->normvect[0],
		scene->camera->normvect[1],
		scene->camera->normvect[2]);
	printf("\nAMBIENT LIGHT:\n");
	printf("Ratio: %f\n", scene->ambient->ratio);
	printf("color: %x\n",
		scene->ambient->color);
	printf("\nSPOT LIGHTS:\n");
	t_spot	*curr = scene->spots;
	while (curr)
	{
		printf("\nRatio: %f\n", curr->ratio);
		printf("color: %x\n", curr->color);
		printf("Source: %lf, %lf, %lf\n",
			curr->source[0],
			curr->source[1],
			curr->source[2]);
		curr = curr->next;
	}
	printf("\nOBJECTS:\n");
	t_object	*curr2 = scene->objects;
	while (curr2)
	{
		printf("\nType: %d\n", curr2->type);
		printf("Center: %lf, %lf, %lf\n",
			curr2->center[0],
			curr2->center[1],
			curr2->center[2]);
		printf("Color: %x\n", curr2->color);
		printf("Norm vector: %lf, %lf, %lf\n",
			curr2->normvect[0],
			curr2->normvect[1],
			curr2->normvect[2]);
		printf("Diameter: %lf\n",
			curr2->radius * 2);
		printf("Height: %lf\n",
			curr2->height);
		curr2 = curr2->next;
	}
	printf("\n*******DONE PARSING***************\n");
	printf("\n*******VECTOR UTILS***************\n");
	t_vector	a = {2.5, -1.3, 3.7};
	t_vector	b = {0.8, 2.4, -1.6};
	printf("\nVector a: %lf, %lf, %lf\n", a[0], a[1], a[2]);
	printf("Vector b: %lf, %lf, %lf\n", b[0], b[1], b[2]);
	printf("Angle: %f\n", angle(a, b));
	printf("Dot product: %f\n", dot(a, b));
	printf("Norm a and b: %f, %f\n", norm(a), norm(b));
	t_vector	result;
	normalize(a, result);
	printf("Normalized a: %f, %f, %f\n", result[0], result[1], result[2]);
	cross(a, b, result);
	printf("Cross product: %f, %f, %f\n", result[0], result[1], result[2]);
	add(a, b, result);
	printf("Addition: %f, %f, %f\n", result[0], result[1], result[2]);
	subtract(a, b, result);
	printf("Subtraction: %f, %f, %f\n", result[0], result[1], result[2]);
}