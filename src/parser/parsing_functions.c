/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/02/21 14:37:13 by lannur-s         ###   ########.fr       */
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
    // Built-ins 
    
	cmd = parse_pipe(token_head);
//	printf("\n");	
	printf("######END OF parse_cmd######\n");
//	print_cmd(cmd);
	return (cmd);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_token_T **token)
{
    char    *file_name;
    t_token_T *next_tolkien;
    t_token_T *current_token;    

    current_token = *token;  
//   printf("-----printing token list in parse_redirs begining-----\n");          
//        print_token_list(current_token);
// printf("######parse_redirs######\n");
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
            *token = advance_token(&next_tolkien);
            if (((*token)->type != T_REDIRECT_IN) && \
                ((*token)->type != T_REDIRECT_OUT) && \
                ((*token)->type != T_APPEND_OUT))
                    set_read_from((t_redircmd_P *)cmd, 1);            
            break ;
        }
        else if ((current_token)->type == T_REDIRECT_OUT)
        {
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);
            *token = advance_token(&next_tolkien);
            if (((*token)->type != T_REDIRECT_IN) && \
                ((*token)->type != T_REDIRECT_OUT) && \
                ((*token)->type != T_APPEND_OUT))
                    set_write_into((t_redircmd_P *)cmd, 1);
                
            break ;
        }
        else if ((current_token)->type == T_APPEND_OUT)
        {
            cmd = create_redircmd(cmd, file_name, O_WRONLY | O_CREAT, 1);
            *token = advance_token(&next_tolkien);
            break ;
        }
    }
//	print_cmd(cmd);
//    printf("-----printing token list in parse_redirs ending-----\n");          
//    print_token_list(*token);
//    printf ("####exiting parseredir####\n");  
    return (cmd);    
}

t_cmd_P* parse_exec(t_token_T **token)
{
    t_execcmd_P *cmd;
    t_cmd_P *ret;
    int argc;
    
    ret = create_execcmd();
    cmd = (t_execcmd_P*) ret;
    argc = 0;
    ret = parse_redirs(ret, token);
    
    while ((*token)->type != T_PIPE)
    {
//    printf("::::::::::token type = %d\n", (*token)->type);
        if ((*token)->type == T_LINEBREAK)
        {
//            printf ("linebreak reached\n");
            break ;
        }
        if (((*token)->type != T_REDIRECT_IN) && \
            ((*token)->type != T_REDIRECT_OUT) && \
            ((*token)->type != T_APPEND_OUT))
        {
//            printf ("adding command '%s' to cmd\n", (*token)->value);
            cmd->argv[argc] = (*token)->value;
            argc++;
            if (argc >= MAXARGS)
                panic("too many args");
//        printf("printing token list in parse_exec \n");
//       print_token_list(*token);
        *token = advance_token(token);
        }
        ret = parse_redirs(ret, token);
    }
    cmd->argv[argc] = 0;
//	print_cmd(ret);
    return (ret);
}

t_cmd_P* parse_pipe(t_token_T	**token)
{
    t_cmd_P  *cmd;
    
    cmd = parse_exec(token);
    if (search_for(*token, T_PIPE))
    {
        *token = advance_token(token);
        if ((*token)->type != T_WORD)
            panic("syntax error\n");
        cmd = create_pipecmd(cmd, parse_pipe(token));
    }
    printf("-----printing cmd in parse_pipe ending-----\n");          
	print_cmd(cmd);   
    printf ("####exiting parse_pipe####\n");  
    return (cmd);
}