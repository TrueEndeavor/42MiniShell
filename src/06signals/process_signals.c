/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:36:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 10:29:10 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_signals_in_child(int status)
{
	int	last_status;

	last_status = WTERMSIG(status);
	if (last_status == SIGTERM)
		write(STDOUT_FILENO, "\n", 1);
	if (last_status == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (last_status == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	return (last_status + 128);
}

void	process_eof(t_core_struct *core)
{
	ft_free_env(core->env_list);
	free(core);
	printf("exit\n");
}

int	process_signals_in_heredocs(int status)
{
	int	last_status;

	last_status = WTERMSIG(status);
	if (last_status == SIGTERM)
		write(STDOUT_FILENO, "\n", 1);
	return (last_status + 128);
}
