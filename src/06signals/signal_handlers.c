/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/02 13:27:03 by trysinsk         ###   ########.fr       */
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
	if (signum == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		write(1, "\\^\\Quit (core dumped)", 18);
		g_signum = signum;
		rl_redisplay();
	}
}

void	heredoc_sighandler(int signum)
{
	close(0);
	if (signum == SIGINT)
		g_signum = signum;
	write(2, "\n", 1);
}
