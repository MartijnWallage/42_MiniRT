/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:37:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 17:07:38 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT"

void	normalize(t_vector input, t_vector output);
void	cross(t_vector a, t_vector b, t_vector output);
void	dot(t_vector a, t_vector b, t_vector output);
void	add(t_vector a, t_vector b, t_vector output);
void	multiply(t_vector a, double scalar, t_vector output);
double	vec_len(t_vector vec);