/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:37:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 14:00:05 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief 			Computes cross product of two vectors
/// @param a 
/// @param b 
/// @param result 	Cross product of a and b
t_vec3	cross(const t_vec3 a, const t_vec3 b)
{
	t_real	x;
	t_real	y;
	t_real	z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return ((t_vec3){x, y, z});
}

/// @brief 		computes dot product of two vectors.
/// @param a 
/// @param b 
/// @return 	dot product of a and b
t_real	dot(const t_vec3 a, const t_vec3 b)
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
t_vec3	multiply(const t_vec3 a, const t_real scalar)
{
	return ((t_vec3){a.x * scalar, a.y * scalar, a.z * scalar});
}
