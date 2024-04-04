/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/04 10:02:42 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_execcmd_P *ecmd, t_core_struct *core, char *prompt)
{
	unsigned char	ret;

	ret = 0;
	if (ecmd->argv[1] != NULL && ecmd->argv[2] != NULL)
	{
		ft_printf ("exit: too many arguments\n");
		return (1);
	}
	if (((ecmd->argv[1]) && (!ft_isnumber(ecmd->argv[1])))
		|| ((ecmd->argv[1]) && (ecmd->argv[1][1] == '+'
			|| ecmd->argv[1][1] == '-')))
	{
		ft_printf ("exit: %s: numeric argument required\n", ecmd->argv[1]);
		return (2);
	}
	if (ecmd->argv[1] != NULL)
		ret = ft_atoi(ecmd->argv[1]);
	free(ecmd);
	ft_free_tok_list(core->token_head);
	ft_free_env(core->env_list);
	free(core);
	free(prompt);
	rl_clear_history();
	//printf ("exit has a value of %d\n", ret);
	exit (ret);
	exit (core->exit_code);
}
