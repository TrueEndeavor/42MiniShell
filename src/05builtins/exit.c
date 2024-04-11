/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 11:04:53 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit_child(t_core_struct *core, t_cmd_P *fcmd, char **env)
{
	ft_free_cmd(fcmd);
	ft_free_tok_list(core->token_head);
	ft_free_env(core->env_list);
	free(core);
	ft_free(NULL, env);
}

int	exit_ch(t_execcmd_P *ecmd, t_core_struct *core, t_cmd_P *f, char **e)
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
	free_exit_child(core, f, e);
	exit (ret);
}

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
