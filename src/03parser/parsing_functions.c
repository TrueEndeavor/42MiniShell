/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/08 10:05:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*parse_cmd(t_core_struct *core)
{
	t_cmd_P		*cmd;
	t_token_T	*token_list_copy;

	token_list_copy = NULL;
	if (core->token_head == NULL || *core->token_head == NULL)
	{
		return (NULL);
	}
	token_list_copy = (*core->token_head);
	cmd = parse_pipe(core);
	#if DEBUG
	print_cmd(cmd);
	#endif
	(*core->token_head) = token_list_copy;
	return (cmd);
}

t_cmd_P	*parse_redirs(t_cmd_P *cmd, t_core_struct *core)
{
	t_token_T	*next_tolkien;
	t_token_T	*current_token;

	current_token = *(core->token_head);
	while ((search_for(current_token, T_REDIRECT_IN) != NULL) || \
			(search_for(current_token, T_REDIRECT_OUT) != NULL) || \
			(search_for(current_token, T_HEREDOC) != NULL) || \
			(search_for(current_token, T_APPEND_OUT) != NULL))
	{
		next_tolkien = peek_next_token(current_token);
		if (current_token->type != T_HEREDOC)
			{
				//(next_tolkien)->value = ft_expand(core, &(next_tolkien)->value);
				next_tolkien->value = quote(&(next_tolkien)->value, core, 0, 0);
			}
		if ((current_token)->type == T_REDIRECT_IN)
			return (ft_r_in(core, &cmd, next_tolkien));
		else if ((current_token)->type == T_REDIRECT_OUT)
			return (ft_r_out(core, &cmd, next_tolkien));
		else if ((current_token)->type == T_APPEND_OUT)
			return (ft_app_out(core, &cmd, next_tolkien));
		else if ((current_token)->type == T_HEREDOC)
			return (ft_cr_here(core, &cmd, next_tolkien));
	}
	return (cmd);
}

t_cmd_P	*parse_exec(t_core_struct *core)
{
	t_execcmd_P	*cmd;
	t_cmd_P		*ret;
	int			argc;

	ret = create_execcmd();
	cmd = (t_execcmd_P *) ret;
	argc = 0;
	ret = parse_redirs(ret, core);
	while ((*core->token_head)->type != T_PIPE)
	{
		#if DEBUG
		printf("(*core->token_head)->type = %d\n", (*core->token_head)->type);
		#endif
		expand_variables(&(*core->token_head), core);
		//printf("<In parsing_functions > after expansion = %s\n",(*core->token_head)->value);
		if ((*core->token_head)->type == T_EXITCODE)
			(*core->token_head)->value = ft_strdup(ft_itoa(core->exit_code));
		//ft_loop_assign(core);
		//ft_loop_quote(core);
		ft_loop_variable(core);
		if ((*core->token_head)->type == T_LINEBREAK
			|| ((*core->token_head)->type == T_PIPE))
			break ;
		else if (check_redir(core) == 0)
			ft_fill_exec(core, &argc, cmd);
		ret = parse_redirs(ret, core);
	}
	cmd->argv[argc] = 0;
	return (ret);
}

t_cmd_P	*parse_pipe(t_core_struct *core)
{
	t_cmd_P	*cmd;

	cmd = parse_exec(core);
	if (search_for(*core->token_head, T_PIPE))
	{
		*core->token_head = advance_token(core->token_head);
		cmd = create_pipecmd(cmd, parse_pipe(core));
	}
	return (cmd);
}
