/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 20:39:27 by lannur-s         ###   ########.fr       */
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
}

void	child_sighandler(int signum)
{
	(void) signum;
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		g_signum = signum;
		rl_redisplay();
	}
}

void	heredoc_sighandler(int signum)
{
	close(0);
	if (signum == SIGINT)
		g_signum = 128 + signum;
	write(2, "\n", 1);
	rl_redisplay();
	exit(g_signum);
}
