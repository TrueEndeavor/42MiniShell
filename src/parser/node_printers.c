/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:11:57 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/13 12:30:36 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"
#include <stdio.h>

void print_execcmd(t_cmd_P *cmd)
{
    t_execcmd_P *execCmd = (t_execcmd_P *)cmd;
    printf("Type: EXEC_CMD\n");
    for (int i=0; i < MAXARGS; i++)
        printf("argv: %s\n", execCmd->argv[i]);
    // Add any additional fields specific to t_execcmd_P if needed
}

void print_redircmd(t_cmd_P *cmd)
{
    t_redircmd_P *redirectCmd = (t_redircmd_P *)cmd;
    printf("Type: REDIR_CMD\n");
    printf("File: %s\n", redirectCmd->file);
    printf("Mode: %d\n", redirectCmd->mode);
    printf("File Descriptor: %d\n", redirectCmd->fd);
    // Recursively print the sub-command if it's not NULL
    if (redirectCmd->cmd != NULL) {
        printf("Sub-command:\n");
        print_cmd(redirectCmd->cmd);
    }
}

void print_pipecmd(t_cmd_P *cmd)
{
    t_pipecmd_P *pipeCmd = (t_pipecmd_P *)cmd;
    printf("Type: PIPE_CMD\n");
    printf("Left command:\n");
    print_cmd(pipeCmd->left);
    printf("Right command:\n");
    print_cmd(pipeCmd->right);
}

void print_cmd(t_cmd_P *cmd) 
{
    if (cmd == NULL) {
        printf("Command is NULL\n");
        return;
    }
    printf("command type = %d\n",cmd->type);
    switch (cmd->type) {
        case EXEC_CMD:
            print_execcmd(cmd);
            break;
        case REDIR_CMD:
            print_redircmd(cmd);
            break;
        case PIPE_CMD:
            print_pipecmd(cmd);
            break;
        default:
            printf("Unknown command type\n");
            break;
    }
}

