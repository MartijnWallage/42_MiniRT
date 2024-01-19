/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:37:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/19 13:50:39 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	angle(const t_vector a, const t_vector b)
{
	if (norm(a) * norm(b) != 0)
		return (acos(dot(a, b)) / (norm(a) * norm(b)));
	else
		return (0);
}

void	cross(const t_vector a, const t_vector b, t_vector result)
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}

/// @brief 		computes dot product of two vectors.
/// @param a 
/// @param b 
/// @return 	dot product of a and b
double	dot(const t_vector a, const t_vector b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}


/// @brief adds vectors a and b and stores result 
///		   Can also be used for offset.
/// @param a 
/// @param b 
/// @param result
void	add(const t_vector a, const t_vector b, t_vector result)
{
	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];
	result[2] = a[2] + b[2];
}

/// @brief substracting vector b from a. 
///		   Can also be used for negative offset.
/// @param a 
/// @param b 
/// @param result 
void	subtract(const t_vector a, const t_vector b, t_vector result)
{
	result[0] = a[0] - b[0];
	result[1] = a[1] - b[1];
	result[2] = a[2] - b[2];
}

/// @brief scalar multiplication.
/// @param a 
/// @param scalar 
/// @param result 
void	multiply(const t_vector a, const double scalar, t_vector result)
{
	result[0] = a[0] * scalar;
	result[1] = a[1] * scalar;
	result[2] = a[2] * scalar;
}

/// @brief 		computes the norm (length) of given vector.
/// @param vec 	given vector
/// @return 	the norm of vec, as an unsigned double.
double	norm(const t_vector vec)
{
	return (sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]));
}

/// @brief 			normalizes a given vector.
/// @param vec		given vector.
/// @param result 	normalized vector, or 0 vector if norm of vec is 0.
void	normalize(const t_vector vec, t_vector result)
{
	double	scalar;

	if (norm(vec) != 0)
		scalar = 1 / norm(vec);
	else
		scalar = 0;
	multiply(vec, scalar, result);
}
