/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:58:05 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 08:47:14 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expand(t_expand_str *expand, t_core_struct *core)
{
	if (*expand->input == '\'')
	{
		if (expand->state & EX_DOUBLE_QUOTE)
			copy_and_increment(expand);
		else
			change_state(EX_SINGLE_QUOTE, expand);
	}
	else if (*expand->input == '\"')
	{
		if (expand->state & EX_SINGLE_QUOTE)
			copy_and_increment(expand);
		else
			change_state(EX_DOUBLE_QUOTE, expand);
	}
	else if (*expand->input == '$')
	{
		if (expand->state & EX_SINGLE_QUOTE)
			copy_and_increment(expand);
		else
			handle_dollar(expand, core);
	}
	else
		copy_and_increment(expand);
}

char	*expand(t_core_struct *core, t_expand_str *expand)
{
	expand->result = ft_calloc(expand->input_size + 1, sizeof(char));
	if (!expand->result)
		return (NULL);
	while (*expand->input)
	{
		handle_expand(expand, core);
	}
	if (expand->result_size == 0)
	{
		free(expand->result);
		return (NULL);
	}
	return (expand->result);
}

void	init_expand(t_expand_str *expand, char *input)
{
	expand->result = NULL;
	expand->result_size = 0;
	expand->input = input;
	if (input)
		expand->input_size = ft_strlen(input);
	else
		expand->input_size = 0;
	expand->i = 0;
	expand->state = EX_NONE;
}

void	expand_variables(t_token_T **token_string, t_core_struct *core)
{
	char			*tmp;
	t_expand_str	exp_struct;
	t_token_T		*current;

	current = *token_string;
	if (!current || !current->value)
		return ;
	if (current && current->value != NULL)
	{
		init_expand(&exp_struct, current->value);
		tmp = current->value;
		current->value = expand(core, &exp_struct);
		free(tmp);
	}
}
