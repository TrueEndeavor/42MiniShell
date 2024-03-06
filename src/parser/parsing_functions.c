/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/06 09:52:54 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T *search_for(t_token_T *current, int target_token_type)
{
    t_token_T *tok = current;
    if (tok->type == target_token_type)
    {
        return tok;
    }
    return NULL;
}

t_token_T	*peek_next_token(t_token_T *current_token)
{
	if (current_token && current_token->next)
	{
		return (current_token->next);
	}
	return (NULL);
}


t_token_T	*advance_token(t_token_T **current_token)
{
	if (*current_token && (*current_token)->next)
	{
		return ((*current_token)->next);
	}
	return (NULL);
}

t_cmd_P	*parse_cmd(t_core_struct *core)
{
	t_cmd_P		*cmd;
	t_token_T   **token_list_copy;
    
    if (core->token_head == NULL || *core->token_head == NULL)
    {
        return (NULL);
    }
    token_list_copy = core->token_head;
	cmd = parse_pipe(core);
	print_cmd(cmd);
	core->token_head = token_list_copy;
	return (cmd);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_core_struct *core)
{
    char    *file_name;
    t_token_T *next_tolkien;
    t_token_T *current_token;    

    current_token = *(core->token_head);  
    while ((search_for(current_token, T_REDIRECT_IN) != NULL) || \
            (search_for(current_token, T_REDIRECT_OUT) != NULL) || \
            (search_for(current_token, T_HEREDOC) != NULL) || \
            (search_for(current_token, T_APPEND_OUT) != NULL))         
    {
        next_tolkien = peek_next_token(current_token);
        /* if (next_tolkien->type != T_WORD)
            panic("missing file for redirection"); */
        file_name = next_tolkien->value;        
        if ((current_token)->type == T_REDIRECT_IN)
        {
            if (next_tolkien->type == T_VARIABLE)
            {
                // The expand has to happen here
                file_name = get_env(core, file_name);
            }
            cmd = create_redircmd(cmd, file_name, O_RDONLY, 0);
            *core->token_head = advance_token(&next_tolkien);
            if (((*core->token_head)->type != T_REDIRECT_IN) && \
                ((*core->token_head)->type != T_REDIRECT_OUT) && \
                ((*core->token_head)->type != T_APPEND_OUT))
                    set_read_from((t_redircmd_P *)cmd, 1);            
            break ;
        }
        else if ((current_token)->type == T_REDIRECT_OUT)
        {
            if (next_tolkien->type == T_VARIABLE)
            {
                // The expand has to happen here
                file_name = get_env(core, file_name);
            }        
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);
            *core->token_head = advance_token(&next_tolkien);
            if (((*core->token_head)->type != T_REDIRECT_IN) && \
                ((*core->token_head)->type != T_REDIRECT_OUT) && \
                ((*core->token_head)->type != T_APPEND_OUT))
                    set_write_into((t_redircmd_P *)cmd, 1);
                
            break ;
        }
        else if ((current_token)->type == T_APPEND_OUT)
        {
            if (next_tolkien->type == T_VARIABLE)
            {
                // The expand has to happen here
                file_name = get_env(core, file_name);
            }        
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT, 1);
            *core->token_head = advance_token(&next_tolkien);
            break ;
        }
        else if ((current_token)->type == T_HEREDOC)
        {
            cmd = create_herecmd(cmd, file_name);
            *core->token_head = advance_token(&next_tolkien);
            break ;
        }        
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
        // Quoting
        if ((*core->token_head)->type == T_DOUBLE_QUOTED_STRING)
        {
            printf ("value of quote before: %s\n", (*core->token_head)->value);
            //(*core->token_head)->value = quote_string((*core->token_head)->value, core, 2);
            printf ("value of quote after: %s\n", (*core->token_head)->value);
        }
        // End of quoting
        if ((*core->token_head)->type == T_LINEBREAK)
            break ;
        if ((*core->token_head)->type == T_VARIABLE)
        {
            // The expand has to happen here
            cmd->argv[argc] = get_env(core, (*core->token_head)->value);
            argc++;
            if (argc >= MAXARGS)
                panic("too many args");
            *core->token_head = advance_token(core->token_head);
        }
        else if (((*core->token_head)->type != T_REDIRECT_IN) && \
            ((*core->token_head)->type != T_REDIRECT_OUT) && \
            ((*core->token_head)->type != T_APPEND_OUT) && \
            ((*core->token_head)->type != T_HEREDOC))
        {
            cmd->argv[argc] = (*core->token_head)->value;
            argc++;
            if (argc >= MAXARGS)
                panic("too many args");
            *core->token_head = advance_token(core->token_head);
        }
        
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