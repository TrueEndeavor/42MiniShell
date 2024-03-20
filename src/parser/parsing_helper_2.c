/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:26 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/20 14:42:30 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_loop_quote(t_core_struct *co)
{
	while ((*co->token_head)->type == T_DOUBLE_QUOTED_STRING)
	{
		printf ("value of quote before: %s\n", (*co->token_head)->value);
		(*co->token_head)->value = quote_string(&(*co->token_head)->value, co, 0, 0);
		printf ("value of quote after: %s\n", (*co->token_head)->value);
		(*co->token_head)->type = T_WORD;
		if ((*co->token_head)->value[0] == '\0')
			(*co->token_head) = (*co->token_head)->next;
	}
}

void	ft_loop_variable(t_core_struct *c)
{
	while ((*c->token_head)->type == T_VARIABLE)
	{
		(*c->token_head)->value = (dupl(get_env(c, (*c->token_head)->value)));
		(*c->token_head)->type = T_WORD;
		if ((*c->token_head)->value == NULL)
			(*c->token_head) = (*c->token_head)->next;
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
