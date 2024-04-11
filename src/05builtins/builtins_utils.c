/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:57 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 07:05:51 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	contains_only_char(char *str, char c)
{
	str++;
	while (*str != '\0')
	{
		if (*str != c)
			return (false);
		str++;
	}
	return (true);
}

void	get_trimmed_val(char **value_to_set, char *key_value_pair)
{
	char		*val;

	val = get_value(key_value_pair);
	*value_to_set = ft_strtrim(val, " ");
	free(val);
}
