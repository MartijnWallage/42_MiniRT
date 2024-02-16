/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:37:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 11:39:39 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief 			Computes cross product of two vectors
/// @param a 
/// @param b 
/// @param result 	Cross product of a and b
t_vec3	cross(const t_vec3 a, const t_vec3 b)
{
	double	x;
	double	y;
	double	z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return ((t_vec3){x, y, z});
}

/// @brief 		computes dot product of two vectors.
/// @param a 
/// @param b 
/// @return 	dot product of a and b
double	dot(const t_vec3 a, const t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/// @brief adds vectors a and b and stores result 
///		   Can also be used for offset.
/// @param a 
/// @param b 
/// @param result
t_vec3	add(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

/// @brief substracting vector b from a. 
///		   Can also be used for negative offset.
/// @param a 
/// @param b 
/// @param result 
t_vec3	subtract(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

/// @brief scalar multiplication.
/// @param a 
/// @param scalar 
/// @param result 
t_vec3	multiply(const t_vec3 a, const double scalar)
{
	return ((t_vec3){a.x * scalar, a.y * scalar, a.z * scalar});
}

/// @brief 		computes the norm (length) of given vector.
/// @param vec 	given vector
/// @return 	the norm of vec, as an unsigned double.
double	norm(const t_vec3 vec)
{
	return (sqrt(pow2(vec.x) + pow2(vec.y) + pow2(vec.z)));
}

/// @brief 			normalizes a given vector.
/// @param vec		given vector.
/// @param result 	normalized vector, or 0 vector if norm of vec is 0.
t_vec3	normalize(const t_vec3 vec)
{
	double	scalar;

	if (norm(vec) != 0)
		scalar = 1 / norm(vec);
	else
		scalar = 0;
	return (multiply(vec, scalar));
}
