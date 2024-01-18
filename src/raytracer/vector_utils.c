/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:37:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 21:31:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT"

void	cross(t_vector a, t_vector b, t_vector result);
void	dot(t_vector a, t_vector b, t_vector result);
void	add(t_vector a, t_vector b, t_vector result);
void	subtract(t_vector a, t_vector b, t_vector result);
void	scalar_multiply(t_vector a, double scalar, t_vector result);
double	norm(t_vector vec);
void	normalize(t_vector input, t_vector output);
