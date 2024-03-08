/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:05:08 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/08 11:13:35 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int setup_signal(int signal, void (*handler)(int))
{
    struct sigaction s;
    s.sa_handler = handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    return sigaction(signal, &s, NULL);
}

void setup_parent_signals(void)
{
	setup_signal(SIGINT, sighandler_parent);
	setup_signal(SIGQUIT, sighandler_parent);	
}

int setup_child_signals(void)
{
	setup_signal(SIGINT, sighandler_child);
	setup_signal(SIGQUIT, SIG_IGN);
}

int setup_heredoc_signals(void)
{
	setup_signal(SIGINT, sighandler_heredoc);
	setup_signal(SIGQUIT, SIG_IGN);
}