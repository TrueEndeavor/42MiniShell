/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 14:08:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = signum;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		g_signum = signum;
		rl_redisplay();
	}
}

void	heredoc_sighandler(int signum)
{
	t_data      *data;
	
	close(0);
	if (signum == SIGINT)
		g_signum = 128 + signum;
	data = simpleton();
	free_at_signal(data);
	write(2, "\n", 1);
	rl_redisplay();
	exit(g_signum);
}
