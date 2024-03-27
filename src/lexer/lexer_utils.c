/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:06:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/27 15:44:02 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_nested_quotes(const char *str)
{
	bool singleQuoteOpen;
	bool doubleQuoteOpen;
	
	singleQuoteOpen = false;
	doubleQuoteOpen = false;
	while (*str != '\0')
	{
		if ((*str) == '\'')
		{
			if (!doubleQuoteOpen)
				singleQuoteOpen = !singleQuoteOpen;
		}
		else if ((*str) == '\"')
		{
			if (!singleQuoteOpen)
                doubleQuoteOpen = !doubleQuoteOpen;
		}
			str++;
	}
	return (!singleQuoteOpen && !doubleQuoteOpen);
}
