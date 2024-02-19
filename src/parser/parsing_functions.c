/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/02/19 15:30:06 by lannur-s         ###   ########.fr       */
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

t_cmd_P	*parse_cmd(t_token_T **token_head)
{
	t_cmd_P		*cmd;

    if (token_head == NULL || *token_head == NULL)
    {
        return (NULL);
    }
	cmd = parse_pipe(token_head);
	printf("\n");	
	printf("######END OF parse_cmd######\n");
	print_cmd(cmd);
	return (NULL);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_token_T **token)
{
    char    *file_name;
    t_token_T *next_tolkien;
    t_token_T *current_token;    

    current_token = *token;  
  printf("---------printing token list in parse_redirs \n");          
        print_token_list(current_token);
	printf("######parse_redirs######\n");
    while ((search_for(current_token, T_REDIRECT_IN) != NULL) || \
            (search_for(current_token, T_REDIRECT_OUT) != NULL) || \
            (search_for(current_token, T_HEREDOC) != NULL) || \
            (search_for(current_token, T_APPEND_OUT) != NULL))         
    {
        next_tolkien = peek_next_token(current_token);
        if (next_tolkien->type != T_WORD)
            panic("missing file for redirection");
        file_name = next_tolkien->value;        
        if ((current_token)->type == T_REDIRECT_IN)
        {
            cmd = create_redircmd(cmd, file_name, O_RDONLY, 0);
            break ;
        }
        else if ((current_token)->type == T_REDIRECT_OUT)
        {
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);       
            break ;
        }
        else if ((current_token)->type == T_APPEND_OUT)
        {
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT, 1);
            break ;
        }
    }
	print_cmd(cmd);
    *token = advance_token(&current_token);    
    printf ("####exiting parseredir####\n");  
    return (cmd);    
}

t_cmd_P* parse_exec(t_token_T **token)
{
    t_execcmd_P *cmd;
    t_cmd_P *ret;
    int argc;
    t_token_T *current_token;
    
    current_token = *token;
    ret = create_execcmd();
    cmd = (t_execcmd_P*) ret;
    argc = 0;
    ret = parse_redirs(ret, token);
    
    while ((current_token)->type != T_PIPE)
    {
        if ((current_token)->type == T_LINEBREAK)
        {
            printf ("linebreak reached\n");
            break ;
        }
        if ((current_token)->type != T_WORD)
        {
            panic("syntax");
        }
        cmd->argv[argc] = (current_token)->value;
        argc++;
        if (argc >= MAXARGS)
            panic("too many args");
        printf("printing token list in parse_exec \n");            
        print_token_list(current_token);
        current_token = advance_token(&current_token);
        ret = parse_redirs(ret, &current_token);
    }  
    cmd->argv[argc] = 0;
	print_cmd(ret);
    return (ret);
}

t_cmd_P* parse_pipe(t_token_T	**token)
{
    t_cmd_P  *cmd;
    
    cmd = parse_exec(token);
    if (search_for(*token, T_PIPE))
    {
       // cmd = create_pipecmd(cmd, parse_pipe(peek_next_token(*token)));
    }
    return (cmd);
}