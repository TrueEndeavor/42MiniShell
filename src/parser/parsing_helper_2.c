/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:26 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/20 11:26:29 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_loop_quote(t_core_struct *core)
{
    while ((*core->token_head)->type == T_DOUBLE_QUOTED_STRING)
	{
		printf ("value of quote before: %s\n", (*core->token_head)->value);
		(*core->token_head)->value = quote_string(&(*core->token_head)->value, core);
		printf ("value of quote after: %s\n", (*core->token_head)->value);
		(*core->token_head)->type = T_WORD;
		if ((*core->token_head)->value[0] == '\0')
			(*core->token_head) = (*core->token_head)->next;
	}
}
void    ft_loop_variable(t_core_struct *core)
{
    while ((*core->token_head)->type == T_VARIABLE)
	{
		(*core->token_head)->value = (duplicate(get_env(core, (*core->token_head)->value)));
		(*core->token_head)->type = T_WORD;
		if ((*core->token_head)->value == NULL)
			(*core->token_head) = (*core->token_head)->next;
	}
}

void    ft_fill_exec(t_core_struct *core, int *argc, t_execcmd_P *cmd)
{
	cmd->argv[(*argc)] = (*core->token_head)->value;
	(*argc)++;
	if ((*argc) >= MAXARGS)
		panic("too many args");
	*core->token_head = advance_token(core->token_head);
}