/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:36 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/17 17:44:19 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* static int	get_pos_nth_char(char c, char *str, int n)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (str[i] && cnt < n)
	{
		if (str[i] == c)
		{
			cnt++;
			if (cnt == n)
				return (i);
		}
		i++;
	}
	return (-1);
} */

void	str_to_vector(double dest[3], char *str)
{
	char	component[MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 2];
	int		pos;

	pos = 0;
	while (str[pos] != ',')
		pos++;
	ft_strlcpy(component, str, pos + 1);
	dest[0] = ft_strtod(component);
	str += pos + 1;
	pos = 0;
	while (str[pos] != ',')
		pos++;
	ft_strlcpy(component, str, pos + 1);
	dest[1] = ft_strtod(component);
	str += pos + 1;
	pos = 0;
	while (str[pos])
		pos++;
	ft_strlcpy(component, str, pos + 1);
	dest[2] = ft_strtod(component);
}
