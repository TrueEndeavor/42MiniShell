/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/08 10:10:51 by lannur-s         ###   ########.fr       */
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

int	builtin_echo(t_execcmd_P *ecmd, t_core_struct *core)
{
	int i;
	int count_n;
	
	i = 1;
	count_n = 0;
	if ((ecmd->argv[1] == NULL) || (ecmd->argv[1][0] == '\0'))
		return (1);
	if (ft_strcmp(ecmd->argv[i], "?") == 0)
	{
		ft_printf("%d\n", g_exit_code);
		return (0);
	}
	if ((ecmd->argv[1][0] == '-') && (ecmd->argv[1][1] == 'n'))
	{
		if (contains_only_char(ecmd->argv[1], 'n'))
		{
			count_n = 1;
			i++;
		}
	}
	print_the_output(ecmd, i);
	if (count_n < 1)
		ft_printf ("\n");
	(void) core;
	return (0);
}
