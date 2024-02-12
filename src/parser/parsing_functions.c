/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/02/12 19:52:14 by lannur-s         ###   ########.fr       */
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

t_cmd_P	*parse_cmd(t_token_T **token_list)
{
	t_cmd_P		*cmd;
	t_token_T	*current_token;
	t_token_T	*next_token;

    if (token_list == NULL || *token_list == NULL)
    {
        return (NULL);
    }
    current_token = *token_list;
	next_token = peek_next_token(current_token);
	printf("######parse_cmd######\n");
	print_token_list(current_token);
	printf("\n%s\n", token_to_str(current_token));
	printf("%s\n", token_to_str(next_token));
	cmd = parse_pipe(current_token);
	printf("######parse_cmd######\n");
	print_cmd(cmd);
	return (NULL);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_token_T *token)
{
    char    *file_name;
    
    while ((search_for(token, T_REDIRECT_IN) != NULL) || \
            (search_for(token, T_REDIRECT_OUT) != NULL) || \
            (search_for(token, T_HEREDOC) != NULL) || \
            (search_for(token, T_APPEND_OUT) != NULL))         
    {
        if (peek_next_token(token) == NULL)
            panic("missing file for redirection");
        file_name = (peek_next_token(token))->value;        
        if (token->type == T_REDIRECT_IN)
        {
            cmd = create_redircmd(cmd, file_name, O_RDONLY, 0);
            printf("command type = %d\n",cmd->type);
            break ;
        }
        else if (token->type == T_REDIRECT_OUT)
        {
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);       
            break ;
        }
        else if (token->type == T_APPEND_OUT)
        {
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT, 1);
            break ;
        }
    }
	printf("######parse_redirs######\n");
	print_cmd(cmd);    
    return (cmd);    
}

t_cmd_P* parse_exec(t_token_T *token)
{
    t_execcmd_P *ecmd;
    t_cmd_P *cmd;
    int argc;
    
    cmd = create_execcmd();
    ecmd = (t_execcmd_P*) cmd;
printf("command type = %d\n",cmd->type);
printf("token->value = %s\n",token->value);
    argc = 0;
    cmd = parse_redirs(cmd, peek_next_token(token));
    while ((search_for(token, T_PIPE) == NULL))
    {
        if (token == NULL)
            break ;
        if (peek_next_token(token) == NULL)
            panic("syntax");
        ecmd->argv[argc] = token->value;
        argc++;
        if (argc >= MAXARGS)
            panic("too many args");
        cmd = parse_redirs(cmd, peek_next_token(token));
        token = peek_next_token(token);
    }  
    ecmd->argv[argc] = 0;
	printf("######parse_exec######\n");
	print_cmd(cmd);
    return (cmd);
}

t_cmd_P* parse_pipe(t_token_T	*token)
{
    t_cmd_P  *cmd;

    cmd = parse_exec(token);
    if (search_for(token, T_PIPE))
    {
        cmd = create_pipecmd(cmd, parse_pipe(peek_next_token(token)));
    }
    return (cmd);
}