/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:20:53 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/04 13:37:31 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*ft_r_in(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	t_cmd_P			*checker;
	t_redircmd_P	*saver;
	t_cmd_P			*ret;
	int				i;
	
	i = 0;
	checker = (*cmd);
	if (checker->type == REDIR_CMD)
	{
		while (checker->type == REDIR_CMD)
		{
			saver = (t_redircmd_P *) checker;
			checker = saver->cmd;
			i++;
		}
	}
	//tok->value = quote (&tok->value, core, 0, 0);
	ret = create_redircmd((checker), (tok)->value, O_RDONLY, 0);
	*core->token_head = advance_token(&tok);
	if (((*core->token_head)->type != T_REDIRECT_IN) && \
		((*core->token_head)->type != T_REDIRECT_OUT) && \
		((*core->token_head)->type != T_APPEND_OUT) && \
		(ft_double_redir((*core->token_head), T_HEREDOC) == 0) && \
		(ft_double_redir((*core->token_head), T_REDIRECT_IN) == 0))
		set_read_from((t_redircmd_P *)ret, 1);
	if (i > 0)
	{
		saver->cmd = ret;
		return ((*cmd));
	}
	else
		return (ret);
}

t_cmd_P	*ft_r_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	t_cmd_P			*checker;
	t_redircmd_P	*saver;
	t_cmd_P			*ret;
	int				i;
	
	i = 0;
	checker = (*cmd);
	if (checker->type == REDIR_CMD)
	{
		while (checker->type == REDIR_CMD)
		{
			saver = (t_redircmd_P *) checker;
			checker = saver->cmd;
			i++;
		}
	}
	//tok->value = quote (&tok->value, core, 0, 0);
	ret = create_redircmd((checker), (tok)->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 1);
	*core->token_head = advance_token(&tok);
	if (((*core->token_head)->type != T_REDIRECT_IN) && \
		((*core->token_head)->type != T_REDIRECT_OUT) && \
		((*core->token_head)->type != T_APPEND_OUT) && \
		(ft_double_redir((*core->token_head), T_REDIRECT_OUT) == 0) && \
		(ft_double_redir((*core->token_head), T_APPEND_OUT) == 0))
		set_write_into((t_redircmd_P *)ret, 1);
	if (i > 0)
	{
		saver->cmd = ret;
		return ((*cmd));
	}
	else
		return (ret);
}

t_cmd_P	*ft_app_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok)
{
	t_cmd_P			*checker;
	t_redircmd_P	*saver;
	t_cmd_P			*ret;
	int				i;
	
	i = 0;
	checker = (*cmd);
	if (checker->type == REDIR_CMD)
	{
		while (checker->type == REDIR_CMD)
		{
			saver = (t_redircmd_P *) checker;
			checker = saver->cmd;
			i++;
		}
	}
	//tok->value = quote (&tok->value, core, 0, 0);
	ret = create_redircmd(checker, (tok)->value, \
			O_WRONLY | O_CREAT | O_APPEND, 1);
	*core->token_head = advance_token(&tok);
	if (((*core->token_head)->type != T_REDIRECT_IN) && \
		((*core->token_head)->type != T_REDIRECT_OUT) && \
		((*core->token_head)->type != T_APPEND_OUT) && \
		(ft_double_redir((*core->token_head), T_REDIRECT_OUT) == 0) && \
		(ft_double_redir((*core->token_head), T_APPEND_OUT) == 0))
		set_write_into((t_redircmd_P *)ret, 1);
	if (i > 0)
	{
		saver->cmd = ret;
		return ((*cmd));
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
		#if DEBUG
		printf ("got here...doc heh\n");
		#endif
		free((tok)->value);
		(tok)->value = ft_strdup("");
	}
	else if (ft_slen((tok)->value) != 0 && (tok)->value[0] == '\"')
		(tok)->value = ft_ex_here(&(tok)->value);
	#if DEBUG
	printf ("regular here...doc heh\n");
	#endif
	(*cmd) = create_herecmd((*cmd), (tok)->value);
	*core->token_head = advance_token(&tok);
	*core->hcmd[core->ih] = (*cmd);
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
