/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/29 10:05:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_execcmd_P *ecmd, t_core_struct *core, char *prompt)
{
	unsigned char	ret;

	ret = 0;
	if (ecmd->argv[1] != NULL && ecmd->argv[2] != NULL)
	{
		printf ("exit: too many arguments\n");
		return (1);
	}
	if (((ecmd->argv[1]) && (!ft_isnumber(ecmd->argv[1])))
		|| ((ecmd->argv[1]) && (ecmd->argv[1][1] == '+'
			|| ecmd->argv[1][1] == '-')))
	{
		printf ("exit: %s: numeric argument required\n", ecmd->argv[1]);
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
	printf ("exit has a value of %d\n", ret);
	exit (ret);
}
