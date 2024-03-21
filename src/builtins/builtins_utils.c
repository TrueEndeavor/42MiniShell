/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:57 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/21 05:07:38 by lannur-s         ###   ########.fr       */
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
