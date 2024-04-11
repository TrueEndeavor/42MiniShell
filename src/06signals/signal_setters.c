/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:05:08 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 09:28:58 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_signal(int signal, void (*handler)(int))
{
	struct sigaction	s;

	s.sa_handler = handler;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	return (sigaction(signal, &s, NULL));
}

void	setup_readline_signals(void)
{
	setup_signal(SIGINT, readline_sighandler);
	setup_signal(SIGQUIT, readline_sighandler);
}

void	setup_mother_signals(void)
{
	setup_signal(SIGINT, SIG_IGN);
	setup_signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	setup_signal(SIGINT, child_sighandler);
	setup_signal(SIGQUIT, child_sighandler);
}

void	setup_heredoc_signals(void)
{
	setup_signal(SIGINT, heredoc_sighandler);
	setup_signal(SIGQUIT, SIG_IGN);
}
