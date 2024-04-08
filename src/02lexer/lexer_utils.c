/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:06:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 14:46:33 by trysinsk         ###   ########.fr       */
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
	if (single_quote_open)
		ft_printf(" unexpected EOF while looking for matching `\''\n");
	if (double_quote_open)
		ft_printf(" unexpected EOF while looking for matching `\"'\n");
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

bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || \
		c == '\n' || c == '\r' || c == '\v' || \
		c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
