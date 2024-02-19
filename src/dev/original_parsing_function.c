/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   original_parsing_function.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:43:08 by trysinsk          #+#    #+#             */
/*   Updated: 2024/02/19 13:50:04 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*for now we seems to be having 6 function, not all are going to be usefull but heh...
might as well get them here.*/
////////////list begins here//////////////////
/*parsecmd:theoreticaly null terminate the entire string of command but
we probably wont need it*/

struct cmd* parsecmd(char *s)
{
    char *es;
    struct cmd  *cmd;

    es = s + strlen(s);
    cmd = parseline(&s, es);
    peek(&s, es, "");
    if (s != es)
    {
        fpintf(2, "leftovers: %s\n", s);
        panic("syntax");
    }
    nulteminate(cmd);
    return (cmd);
}

/*-parseexec:
calls parseredirs folowed by one or mutliple word and redirections calls.*/

struct cmd* pareseexec(char **ps, char *es)
{
    char    *q;
    char    *eq;
    struct execcmd *cmd;
    struct cmd *ret;
    
    if (peek(ps, es, "("))
        return parseblock(ps, es,);
    ret = execmd();
    cmd = (struct execcmd*)ret;

    argc = 0;
    ret = parseredirs(ret, ps, es);
    while (!peek(ps, es, "|)&;"))
    {
        if ((tok=gettoken(ps, es, &q, &eq)) == 0)
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

/*-parseredirs:
treats the redirection(s) symbol followed by a word preferably the file descriptor.*/

struct cmd* parseredirs(struct cmd *cmd, char **ps, char *es)
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

/*-parsepipe:
calls the parseexec function, may be followed by a Pipe.*/

struct cmd* parsepipe(char **ps, char *es)
{
    struct cmd  *cmd;

    cmd = parseexec(ps, es);
    if (peek(ps, es, "|"))
    {
        gettoken(ps, es, 0, 0);
        cmd = pipecmd(cmd, parsepipe(ps, es));
    }
    return (cmd);
}

/*-parseline:
calls the parsepipe function followed by one or multiple '&' character and if there is
a ';' character, calls the parseline function*/

struct cmd* parseline(char **ps, char *es)
{
    struct cmd  *cmd;
    
    cmd = parsepipe(ps, es);
    while (peek(ps, es, "&"));
    {
        gettoken(ps, es, 0, 0);
        cmd = backcmd(cmd);
    }
    if (peek(ps, es, ";"))
    {
        gettoken(ps, es, 0, 0);
        cmd = listcmd(cmd, parseline(ps, es));
    }
    return (cmd);
}

/*-parseblock:
check for parenthesis and if true, calls the parseline function folowed by the closing parenthesis
then calls the parseredir function*/

struct cmd* parseblock(char **ps, char *es)
{
    struct cmd  *cmd;
    
    if (!peek(ps, es, "("))
        panic("parsebloc");
    gettoken(ps, es, 0, 0);
    cmd = parseline(ps, es);
    if (!peek(ps, es, ")"))
        panic("syntax missing ')'");
    gettoken(ps, es, 0, 0);
    cmd = parseredirs(cmd, ps, es);
    return (cmd);
}
