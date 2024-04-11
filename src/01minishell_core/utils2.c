/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:01:06 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 11:18:56 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
	}
	return (1);
}

void	frhere(t_herecmd_P *hcmd, t_core_struct *c, char *s, t_cmd_P *fcmd)
{
	free (s);
	close (hcmd->fd);
	ft_free_cmd(fcmd);
	ft_free_tok_list(c->token_head);
	ft_free_env(c->env_list);
	free(c);
}

void	here_ext(char *line, t_herecmd_P *hcmd)
{
	ft_putstr_fd(line, hcmd->fd);
	ft_putstr_fd("\n", hcmd->fd);
	free(line);
}

bool	check_for_exit_code(int exit_code, int signum)
{
	if (exit_code == signum)
		return (false);
	return (true);
}
