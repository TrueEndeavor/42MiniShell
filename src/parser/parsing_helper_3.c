/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:20:53 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/21 10:54:27 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*ft_r_in(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	(*cmd) = create_redircmd((*cmd), (tok)->value, O_RDONLY, 0);
	*core->token_head = advance_token(&tok);
	if (((*core->token_head)->type != T_REDIRECT_IN) && \
		((*core->token_head)->type != T_REDIRECT_OUT) && \
		((*core->token_head)->type != T_APPEND_OUT))
		set_read_from((t_redircmd_P *)(*cmd), 1);
	return ((*cmd));
}

t_cmd_P	*ft_r_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	(*cmd) = create_redircmd((*cmd), (tok)->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 1);
	*core->token_head = advance_token(&tok);
	if (((*core->token_head)->type != T_REDIRECT_IN) && \
		((*core->token_head)->type != T_REDIRECT_OUT) && \
		((*core->token_head)->type != T_APPEND_OUT))
		set_write_into((t_redircmd_P *)(*cmd), 1);
	return ((*cmd));
}

t_cmd_P	*ft_app_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	(*cmd) = create_redircmd((*cmd), (tok)->value, \
			O_WRONLY | O_CREAT | O_APPEND, 1);
	*core->token_head = advance_token(&tok);
	if (((*core->token_head)->type != T_REDIRECT_IN) && \
		((*core->token_head)->type != T_REDIRECT_OUT) && \
		((*core->token_head)->type != T_APPEND_OUT))
		set_write_into((t_redircmd_P *)(*cmd), 1);
	return ((*cmd));
}

t_cmd_P	*ft_cr_here(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	if ((tok)->type == T_VARIABLE)
		(tok)->value = ft_here(&(tok)->value);
	(*cmd) = create_herecmd((*cmd), (tok)->value);
	*core->token_head = advance_token(&tok);
	return ((*cmd));
}
