/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:06:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 08:38:02 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	l_within_single_quote(int *i, char **str, bool *single_quote_open)
{
	while ((*str)[*i] != '\0')
	{
		if ((*str)[*i] == '\'')
		{
			*single_quote_open = !(*single_quote_open);
			if (!(*single_quote_open))
				break ;
		}
		(*i)++;
	}
}

void	l_within_double_quote(int *i, char **str, bool *double_quote_open)
{
	while ((*str)[*i] != '\0')
	{
		if ((*str)[*i] == '\"')
		{
			*double_quote_open = !(*double_quote_open);
			if (!(*double_quote_open))
				break ;
		}
		(*i)++;
	}
}

void	quote_syntax_error(bool single_quote_open, bool double_quote_open)
{
	if (single_quote_open)
		ft_printf(" unexpected EOF while looking for matching `\''\n");
	if (double_quote_open)
		ft_printf(" unexpected EOF while looking for matching `\"'\n");
}

bool	is_nested_quotes(char *str)
{
	int		i;
	bool	single_quote_open;
	bool	double_quote_open;

	i = 0;
	single_quote_open = false;
	double_quote_open = false;
	while (str[i] != '\0')
	{
		if ((str[i]) == '\'')
		{
			l_within_single_quote(&i, &str, &single_quote_open);
			if (str[i] == '\0')
				break ;
		}
		else if (str[i] == '\"')
		{
			l_within_double_quote(&i, &str, &double_quote_open);
			if (str[i] == '\0')
				break ;
		}
		i++;
	}
	quote_syntax_error(single_quote_open, double_quote_open);
	return (!single_quote_open && !double_quote_open);
}

void	print_token_list(t_token_T *token_head)
{
	if (token_head)
	{
		while (token_head->next)
		{
			token_head = token_head->next;
		}
	}
}
