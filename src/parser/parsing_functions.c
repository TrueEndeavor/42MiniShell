/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/02/07 18:48:27 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char		*es;
	t_cmd_P		*cmd;
	t_token_T	*current_token;
	t_token_T	*next_token;

	current_token = *token_list;
	next_token = peek_next_token
/* 	es = s + strlen(s);
    cmd = parseline(&s, es);
    peek(&s, es, ""); */
    if (s != es)
    {
        printf(2, "leftovers: %s\n", s);
        panic("syntax");
    }
    nulteminate(cmd);
    return (cmd);
}

t_cmd_P* parese_exec(t_token_T *token_list)
{
    char    *q;
    char    *eq;
    t_execcmd_P *cmd;
    t_cmd_P *ret;
    
    if (peek(ps, es, "("))
        return parseblock(ps, es,);
    ret = execmd();
    cmd = (t_execcmd_P*)ret;

    argc = 0;
    ret = parseredirs(ret, ps, es);
    while (!peek(ps, es, "|)&;"))
    {
        if ((tok=gettoen(ps, es, &q, &eq)) == 0)
            break ;
        if (tok != 'a'/*word*/)
            panic("syntax");
        cmd->argv[argc] = q;
        cmd->eargv[argc] = eq;
        argc++;
        if (argc >= MAXARGS)
            panic("too many args");
            ret = parseredirs(ret, ps, es);
    }
    cmd->argv[argc] = 0;
    cmd->eargv[argc] = 0;
    return (ret);
}

t_cmd_P* parse_redirs(t_cmd_P *cmd, t_token_T *token_list)
{
    int tok;
    char    *q;
    char    *eq;
    
    while (peek(ps, es, "<>"))
    {
        tok = gettoken(ps, es, 0, 0);
        if (gettoken(ps, es, &q, &es) != 'a'/*WORD*/)
            panic("missing file for redirection");
        if (tok == '<'/*REDIRECT_IN*/)
        {
            cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
            break ;
        }
        else if (tok == '>'/*REDIRECT_OUT*/)
        {
            cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE|O_TRUNC, 1);
            break ;
        }
        else if (tok == '>>'/*APPEND_OUT*/)
        {
            cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
            break ;
        }
    }
    return (cmd);    
}

t_cmd_P* parse_pipe(t_token_T *token_list)
{
    t_cmd_P  *cmd;

    cmd = parseexec(ps, es);
    if (peek(ps, es, "|"))
    {
        gettoken(ps, es, 0, 0);
        cmd = pipecmd(cmd, parsepipe(ps, es));
    }
    return (cmd);
}

