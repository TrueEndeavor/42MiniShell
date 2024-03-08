/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/08 11:46:14 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>

void	setup_parent_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);

void	parent_sighandler(int signum);
void	child_sighandler(int signum);
void	heredoc_sighandler(int signum);

#endif