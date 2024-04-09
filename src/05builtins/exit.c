/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 10:12:00 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_execcmd_P *ecmd, t_core_struct *core, char *prompt)
{
	free(ecmd);
	ft_free_tok_list(core->token_head);
	ft_free_env(core->env_list);
	free(core);
	free(prompt);
	rl_clear_history();
}

int	builtin_exit(t_execcmd_P *ecmd, t_core_struct *core, char *prompt)
{
	unsigned char	ret;

	if (((ecmd->argv[1]) && (!ft_isnumber(ecmd->argv[1])))
		|| ((ecmd->argv[1]) && (ecmd->argv[1][1] == '+'
			|| ecmd->argv[1][1] == '-')))
	{
		ft_printf (" numeric argument required\n");
		core->exit_code = 2;
		return (core->exit_code);
	}
	if (ecmd->argv[1] != NULL && ecmd->argv[2] != NULL)
	{
		ft_printf (" too many arguments\n");
		core->exit_code = 1;
		return (core->exit_code);
	}
	if (ecmd->argv[1] != NULL)
		core->exit_code = ft_atoi(ecmd->argv[1]);
	ret = core->exit_code;
	free_exit(ecmd, core, prompt);
	exit (ret);
}
