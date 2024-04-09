/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:20:53 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/09 09:10:20 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*ft_r_in(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*saver;
	t_cmd_P			*ret;

	i = 0;
	checker = (*m);
	if (checker->type == REDIR_CMD)
	{
		while (checker->type == REDIR_CMD)
		{
			saver = (t_redircmd_P *) checker;
			checker = saver->cmd;
			i++;
		}
	}
	ret = create_redircmd((checker), (t)->value, O_RDONLY, 0);
	*c->token_head = advance_token(&t);
	if (i > 0)
	{
		saver->cmd = ret;
		return ((*m));
	}
	else
		return (ret);
}

t_cmd_P	*ft_r_out(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*saver;
	t_cmd_P			*ret;

	i = 0;
	checker = (*m);
	if (checker->type == REDIR_CMD)
	{
		while (checker->type == REDIR_CMD)
		{
			saver = (t_redircmd_P *) checker;
			checker = saver->cmd;
			i++;
		}
	}
	ret = create_redircmd((checker), (t)->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 1);
	*c->token_head = advance_token(&t);
	if (i > 0)
	{
		saver->cmd = ret;
		return ((*m));
	}
	else
		return (ret);
}

t_cmd_P	*ft_app_out(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*saver;
	t_cmd_P			*ret;

	i = 0;
	checker = (*m);
	if (checker->type == REDIR_CMD)
	{
		while (checker->type == REDIR_CMD)
		{
			saver = (t_redircmd_P *) checker;
			checker = saver->cmd;
			i++;
		}
	}
	ret = create_redircmd(checker, (t)->value, \
			O_WRONLY | O_CREAT | O_APPEND, 1);
	*c->token_head = advance_token(&t);
	if (i > 0)
	{
		saver->cmd = ret;
		return ((*m));
	}
	else
		return (ret);
}

t_cmd_P	*ft_cr_here(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	if ((tok)->type == T_VARIABLE)
		(tok)->value = ft_here(&(tok)->value);
	else if (ft_strcmp ((tok)->value, "\"\"") == 0)
	{
		free((tok)->value);
		(tok)->value = ft_strdup("");
	}
	else if (ft_slen((tok)->value) != 0 && (tok)->value[0] == '\"')
		(tok)->value = ft_ex_here(&(tok)->value);
	(*cmd) = create_herecmd((*cmd), (tok)->value);
	*core->token_head = advance_token(&tok);
	(core->hcmd)[core->ih] = (*cmd);
	core->ih += 1;
	return ((*cmd));
}

int	check_redir(t_core_struct *core)
{
	if (((*core->token_head)->type != T_REDIRECT_IN)
		&& ((*core->token_head)->type != T_REDIRECT_OUT)
		&& ((*core->token_head)->type != T_APPEND_OUT)
		&& ((*core->token_head)->type != T_HEREDOC))
		return (0);
	else
		return (1);
}
