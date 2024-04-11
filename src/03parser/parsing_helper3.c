/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:20:53 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/11 10:34:59 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*ft_r_in(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*rsaver;
	t_herecmd_P		*hsaver;
	t_cmd_P			*ret;
	t_cmd_P			*saver;

	rsaver = NULL;
	hsaver = NULL;
	checker = (*m);
	saver = mul(&checker, &hsaver, &rsaver, &i);
	ret = create_redircmd((checker), (t)->value, O_RDONLY, 0);
	*c->token_head = advance_token(&t);
	if (i > 0)
	{
		if (saver->type == REDIR_CMD)
			rsaver->cmd = ret;
		else if (saver->type == HERE_CMD)
			hsaver->cmd = ret;
		return ((*m));
	}
	return (ret);
}

t_cmd_P	*ft_r_out(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*rsaver;
	t_herecmd_P		*hsaver;
	t_cmd_P			*ret;
	t_cmd_P			*saver;

	rsaver = NULL;
	hsaver = NULL;
	checker = (*m);
	saver = mul(&checker, &hsaver, &rsaver, &i);
	ret = create_redircmd((checker), (t)->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 1);
	*c->token_head = advance_token(&t);
	if (i > 0)
	{
		if (saver->type == REDIR_CMD)
			rsaver->cmd = ret;
		else if (saver->type == HERE_CMD)
			hsaver->cmd = ret;
		return ((*m));
	}
	return (ret);
}

t_cmd_P	*ft_app_out(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*rsaver;
	t_herecmd_P		*hsaver;
	t_cmd_P			*ret;
	t_cmd_P			*saver;

	rsaver = NULL;
	hsaver = NULL;
	checker = (*m);
	saver = mul(&checker, &hsaver, &rsaver, &i);
	ret = create_redircmd(checker, (t)->value, \
			O_WRONLY | O_CREAT | O_APPEND, 1);
	*c->token_head = advance_token(&t);
	if (i > 0)
	{
		if (saver->type == REDIR_CMD)
			rsaver->cmd = ret;
		else if (saver->type == HERE_CMD)
			hsaver->cmd = ret;
		return ((*m));
	}
	return (ret);
}

t_cmd_P	*ft_cr_here(t_core_struct *c, t_cmd_P **m, t_token_T *t, int i)
{
	t_cmd_P			*checker;
	t_redircmd_P	*rsaver;
	t_herecmd_P		*hsaver;
	t_cmd_P			*ret;
	t_cmd_P			*saver;

	rsaver = NULL;
	hsaver = NULL;
	checker = (*m);
	saver = mul(&checker, &hsaver, &rsaver, &i);
	ft_here_helper(c, m, t);
	ret = create_herecmd(checker, (t)->value);
	*c->token_head = advance_token(&t);
	(c->hcmd)[c->ih] = ret;
	c->ih += 1;
	if (i > 0)
	{
		if (saver->type == REDIR_CMD)
			rsaver->cmd = ret;
		else if (saver->type == HERE_CMD)
			hsaver->cmd = ret;
		return ((*m));
	}
	return (ret);
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
