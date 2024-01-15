/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 14:40:29 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_str_array(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
		free(chars[i++]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if ((s1 && !s2) || (!s1 && s2))
		return (1);
	if (!s1 && !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
		i++;
	if (i > 0)
		return (s1[i - 1] - s2[i - 1]);
	return (s1[i] - s2[i]);
}

int	get_str_array_len(char **chars)
{
	int i;

	i = 0;
	while (chars[i])
		i++;
	return (i);
}

int	is_numstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf("%s IS NOT\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}
