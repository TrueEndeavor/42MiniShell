/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:01:06 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/02 14:54:09 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
	}
	return (1);
}
