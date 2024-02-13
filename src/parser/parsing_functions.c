/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/02/13 12:17:03 by lannur-s         ###   ########.fr       */
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
	cmd = parse_pipe(current_token);
	printf("\n");	
	printf("######END OF parse_cmd######\n");
	print_cmd(cmd);
	return (NULL);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_token_T *token)
{
    char    *file_name;
    t_cmd_P *tmp;
  
    while ((search_for(token, T_REDIRECT_IN) != NULL) || \
            (search_for(token, T_REDIRECT_OUT) != NULL) || \
            (search_for(token, T_HEREDOC) != NULL) || \
            (search_for(token, T_APPEND_OUT) != NULL))         
    {
	printf("======Inside while loop======\n");    
        if (peek_next_token(token) == NULL)
            panic("missing file for redirection");
        file_name = (peek_next_token(token))->value;        
        if (token->type == T_REDIRECT_IN)
        {
        printf("<---constructing redircmd with T_REDIRECT_IN ----->\n");
            tmp = create_redircmd(cmd, file_name, O_RDONLY, 0);
            cmd = tmp;
            break ;
        }
        else if (token->type == T_REDIRECT_OUT)
        {printf("<---constructing redircmd with T_REDIRECT_OUT ----->\n");
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);       
            break ;
        }
        else if (token->type == T_APPEND_OUT)
        {printf("<---constructing redircmd with T_APPEND_OUT ----->\n");
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
    t_execcmd_P *cmd;
    t_cmd_P *ret;
    int argc;
    
    ret = create_execcmd();
    cmd = (t_execcmd_P*) ret;
    argc = 0;
printf("current token in parse_exec\n");	    
printf("token->type = %d\n",token->type);
printf("token->value = %s\n",token->value); 
    ret = parse_redirs(ret, token);
    
    while (token->type != T_PIPE)
    {
        if (token == NULL)
            break ;
        if (peek_next_token(token) == NULL)
            panic("syntax");
        cmd->argv[argc] = token->value;
        argc++;
        if (argc >= MAXARGS)
            panic("too many args");
        ret = parse_redirs(ret, peek_next_token(token));
        token = peek_next_token(token);
    }  
    cmd->argv[argc] = 0;
	printf("######parse_exec######\n");
	print_cmd(ret);
    return (ret);
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