/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:33:58 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 11:51:38 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief calculate the minimum of two values if positive
/// @param value1 first value
/// @param value2 second value
/// @return the minimal positive of the inputs, if both negative -1
t_real	ft_min_positive(t_real value1, t_real value2)
{
	if (value1 > value2 && value2 >= 0)
		return (value2);
	if (value1 >= 0)
		return (value1);
	return (-1);
}

/// @brief computes the square of the input parameter
/// @param value given number
/// @return square of the input
t_real	pow2(t_real value)
{
	return (value * value);
}

t_real	ft_abs(t_real value)
{
	if (value >= 0)
		return (value);
	return (-value);
}

t_real	norm2(t_vec3 vector)
{
	return (pow2(vector.x) + pow2(vector.y) + pow2(vector.z));
}
