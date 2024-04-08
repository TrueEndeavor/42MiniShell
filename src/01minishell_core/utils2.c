/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:01:06 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 11:52:11 by trysinsk         ###   ########.fr       */
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
