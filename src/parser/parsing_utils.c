/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:44:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/20 17:31:54 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_assignment_word(char *str)
{
	char *position;
	int len;
	int index;
	
	index = 0;
	position = ft_strrchr(str, '=');
	if(position)
	   index = position - str;
	len = strlen(str);
	if (index == (len - 1))
		return (true);
	return (false);
}