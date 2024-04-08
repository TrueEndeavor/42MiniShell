/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:26 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/08 14:05:32 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_loop_assign(t_core_struct *core)
{
	t_token_T	*next_token;
	t_token_T	*current_token;
	t_token_T	*temp_token;
	char		*combined_value;

	combined_value = NULL;
	current_token = *(core->token_head);
	if (current_token->type == T_WORD
		&& is_assignment_word(current_token->value))
	{
		temp_token = current_token;
		next_token = peek_next_token(current_token);
		if (next_token && next_token->type == T_DOUBLE_QUOTED_STRING)
		{
			next_token->value = quote(&(*next_token).value, core, 0, 0);
			combined_value = ft_strjoin(temp_token->value, next_token->value);
			free(current_token->value);
			current_token->value = combined_value;
			current_token->next = next_token->next;
			free(next_token);
		}
	}
}*/

void	ft_loop_quote(t_core_struct *c)
{
	(*c->token_head)->value = quote(&(*c->token_head)->value, c, 0, 0);
}

void	ft_loop_variable(t_core_struct *c)
{
	if ((*c->token_head)->type == T_VARIABLE)
	{
		(*c->token_head)->value = (dupl(get_env(c, (*c->token_head)->value)));
		if ((*c->token_head)->value == NULL)
		{
			free((*c->token_head)->value);
			(*c->token_head)->value = ft_strdup("");
		}
	}
}

void	ft_fill_exec(t_core_struct *core, int *argc, t_execcmd_P *cmd)
{
	cmd->argv[(*argc)] = (*core->token_head)->value;
	(*argc)++;
	if ((*argc) >= MAXARGS)
		panic("too many args");
	*core->token_head = advance_token(core->token_head);
}
