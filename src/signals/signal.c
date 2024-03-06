/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:05:08 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/06 17:54:14 by lannur-s         ###   ########.fr       */
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
}

void set_signal_receiver_readline(void)
{
    // 3 possibilities - just like that, static, malloc from the main
	struct sigaction readline_sig;
	struct sigaction readline_sig1;
	
	readline_sig.sa_handler = sighandler_readline;
	readline_sig.sa_flags = 0;
	sigemptyset(&readline_sig.sa_mask);
	sigaction(SIGINT, &readline_sig, NULL);
	
	
	
	readline_sig1.sa_handler = SIG_IGN;
	readline_sig1.sa_flags = 0;
	sigemptyset(&readline_sig1.sa_mask);
	sigaction(SIGQUIT, &readline_sig1, NULL);	
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