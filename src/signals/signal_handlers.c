/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/13 19:08:15 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_sighandler(int signum) 
{
	if (signum == SIGINT)
	{
		//g_exit_code = 130;
		g_exit_code = signum; // to say that I got hit by a signal
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_sighandler(int signum)
{
	printf("inside child_sighandler");
/* 	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	} */
	if (signum == SIGQUIT)
	{
	    write(1, "\33[2K\r", 5);
		rl_on_new_line();
		write(1, "\\^\\Quit (core dumped)",18);
		//g_exit_code = 131;
		rl_redisplay();
	}
}

void	heredoc_sighandler(int signum)
{
	//check before close(0);
	if (signum == SIGINT)
		g_exit_code = 1;
	write(2, "\n", 1);
}