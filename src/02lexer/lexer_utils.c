/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:06:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 08:50:19 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_nested_quotes(const char *str)
{
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	while (*str != '\0')
	{
		if ((*str) == '\'')
		{
			if (!double_quote_open)
				single_quote_open = !single_quote_open;
		}
		else if ((*str) == '\"')
		{
			if (!single_quote_open)
				double_quote_open = !double_quote_open;
		}
		str++;
	}
	return (!single_quote_open && !double_quote_open);
}

void	print_token_list(t_token_T *token_head)
{
	if (token_head)
	{
		printf("Token type = %d & the value is = %s\n", token_head->type, \
			token_head->value);
		while (token_head->next)
		{
			token_head = token_head->next;
			printf("Token type = %d & the value is = %s\n", token_head->type, \
				token_head->value);
		}
	}
}

void	extend_string(char **value, char c)
{
	char		*copy;
	int			new_size;

	new_size = ft_strlen(*value) + 2;
	copy = ft_calloc(new_size, sizeof(char));
	if (!copy)
	{
		free(*value);
		return ;
	}
	ft_strlcpy(copy, *value, new_size);
	free(*value);
	*value = ft_calloc(new_size, sizeof(char));
	ft_strlcpy(*value, copy, new_size);
	(*value)[new_size - 2] = c;
	(*value)[new_size - 1] = '\0';
	free(copy);
}
