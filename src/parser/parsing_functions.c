/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/20 18:16:16 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*parse_cmd(t_core_struct *core)
{
	t_cmd_P		*cmd;
	t_token_T   *token_list_copy;
	
	token_list_copy = NULL;
	
	if (core->token_head == NULL || *core->token_head == NULL)
	{
		return (NULL);
	}
	token_list_copy = (*core->token_head);
	cmd = parse_pipe(core);
	print_cmd(cmd);
	(*core->token_head) = token_list_copy;
	
	return (cmd);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_core_struct *core)
{
	t_token_T *next_tolkien;
	t_token_T *current_token;

	current_token = *(core->token_head);  
	while ((search_for(current_token, T_REDIRECT_IN) != NULL) || \
			(search_for(current_token, T_REDIRECT_OUT) != NULL) || \
			(search_for(current_token, T_HEREDOC) != NULL) || \
			(search_for(current_token, T_APPEND_OUT) != NULL))
	{
		next_tolkien = peek_next_token(current_token);
		if ((next_tolkien->type == T_VARIABLE) && (current_token->type != T_HEREDOC))
				(next_tolkien)->value = ft_expand(core, &(next_tolkien)->value);
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

t_cmd_P* parse_exec(t_core_struct *core)
{
	t_execcmd_P *cmd;
	t_cmd_P *ret;
	int argc;
	
	ret = create_execcmd();
	cmd = (t_execcmd_P*) ret;
	argc = 0;
	ret = parse_redirs(ret, core);
	while ((*core->token_head)->type != T_PIPE)
	{
        t_token_T *next_token;
        t_token_T *current_token;
        t_token_T *temp_token;

        current_token = *(core->token_head);
        if (current_token->type == T_WORD && is_assignment_word(current_token->value)) 
        {
            temp_token = current_token;
            next_token = peek_next_token(current_token);
            if (next_token && next_token->type == T_DOUBLE_QUOTED_STRING)
            {
                next_token->value = quote_string(&(*next_token).value, core, 0, 0);
                char *combined_value = ft_strjoin(temp_token->value, next_token->value);
                free(current_token->value);
                current_token->value = combined_value;
                current_token->next = next_token->next;
                free(next_token);
            }
		}
		else
			ft_loop_quote(core);
		ft_loop_variable(core);
		if ((*core->token_head)->type == T_LINEBREAK || ((*core->token_head)->type == T_PIPE))
			break ;
		else if (((*core->token_head)->type != T_REDIRECT_IN) && \
			((*core->token_head)->type != T_REDIRECT_OUT) && \
			((*core->token_head)->type != T_APPEND_OUT) && \
			((*core->token_head)->type != T_HEREDOC))
			ft_fill_exec(core, &argc, cmd);
		ret = parse_redirs(ret, core);
	}
	cmd->argv[argc] = 0;
	return (ret);
}

t_cmd_P* parse_pipe(t_core_struct *core)
{
	t_cmd_P  *cmd;
	
	cmd = parse_exec(core);
	if (search_for(*core->token_head, T_PIPE))
	{
		*core->token_head = advance_token(core->token_head);
		if (((*core->token_head)->type != T_WORD))
			panic("syntax error\n");
		cmd = create_pipecmd(cmd, parse_pipe(core));
	}
	return (cmd);
}