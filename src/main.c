/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/10 07:43:59 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signum;

t_core_struct	*initialize_core(char **envp)
{
	t_core_struct	*core;

	core = malloc(1 * sizeof(t_core_struct));
	if (!core)
	{
		perror("minishell: Memory allocation failed: core structure");
		exit (EXIT_FAILURE);
	}
	core->exit_code = EXIT_SUCCESS;
	if (getenv("USER") == NULL)
		core->env_list = create_dummy_env();
	else
	{
		core->env_list = init_env(envp);
		ft_update_shlvl(core);
	}
	core->ih = 0;
	return (core);
}

int	main(int ac, char *av[], char **envp)
{
	t_core_struct	*core;

	(void) ac;
	(void) av;
	core = NULL;
	core = initialize_core(envp);
	return (display_new_prompt(core));
}
