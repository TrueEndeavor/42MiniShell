/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_constructors2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:25:40 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/11 09:03:33 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*create_herecmd(t_cmd_P *subcmd, char *limiter)
{
	t_herecmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = HERE_CMD;
	cmd->cmd = subcmd;
	cmd->delimiter = limiter;
	return ((t_cmd_P *)cmd);
}
