/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/18 09:34:42 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_the_output(t_execcmd_P *ecmd, int i)
{
	while (ecmd->argv[i] != NULL)
	{
		ft_printf("%s",ecmd->argv[i]);
		ft_printf("%c", ' ');
		i++;
	}
}

bool	contains_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}

int	builtin_echo(t_execcmd_P *ecmd, t_core_struct *core)
{
	int i;
	int count_n;
	
	i = 1;
	count_n = 0;
	if ((ecmd->argv[1] == NULL) || (ecmd->argv[1][0] == '\0'))
	{
		core->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(ecmd->argv[i], "?") == 0)
	{
		ft_printf("%d\n", core->exit_code);
		core->exit_code = 0;
		return (0);
	}
	while (ecmd->argv[i] && contains_n(ecmd->argv[i]))
		i++;
	if (i != 1)
		count_n = 0;
	print_the_output(ecmd, i);
	core->exit_code = 0;
	if (count_n < 1)
		ft_printf ("\n");
	return (0);
}
