/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:05:08 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/07 09:35:57 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * When the user interrupts the terminal with
 * Ctrl + C =  clear the current input line and redisplay the prompt
 */
 // Signals: Readline
void sighandler_readline(int signum) 
{
    // Ctrl+C
	if (signum == SIGINT)
	{
		g_signum = signum;
		rl_replace_line("", 0);
        write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
	    write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
    }
}

void set_signal_receiver_readline(void)
{
	struct sigaction readline_sig;
	
	readline_sig.sa_handler = sighandler_readline;
	readline_sig.sa_flags = SA_RESTART;
	sigemptyset(&readline_sig.sa_mask);
	sigaction(SIGINT, &readline_sig, NULL);
	sigaction(SIGQUIT, &readline_sig, NULL);	
}


void set_signal_receiver_exec(void)
{
	struct sigaction exec_sig;
	
	exec_sig.sa_handler = SIG_IGN;
	exec_sig.sa_flags = 0;
	sigemptyset(&exec_sig.sa_mask);
	sigaction(SIGINT, &exec_sig, NULL);
	sigaction(SIGQUIT, &exec_sig, NULL);
}