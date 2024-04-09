/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 10:21:55 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_the_output(t_execcmd_P *ecmd, int i)
{
	int	start_index;
	int	last_index;

	start_index = i;
	last_index = i - 1;
	while (ecmd->argv[i] != NULL || ecmd->argv[i + 1] != NULL)
	{
		last_index++;
		i++;
	}
	while (ecmd->argv[start_index] != NULL
		|| ecmd->argv[start_index + 1] != NULL)
	{
		ft_putstr_fd(ecmd->argv[start_index], 1);
		if (ecmd->argv[start_index] != NULL && start_index < last_index
			&& ft_strcmp(ecmd->argv[start_index + 1], "$") != 0)
			ft_putstr_fd(" ", 1);
		start_index++;
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
	int	i;
	int	count_n;

	i = 1;
	count_n = 0;
	while (ecmd->argv[i] && contains_n(ecmd->argv[i]))
		i++;
	if ((i != 1) && (count_n < 2))
		count_n = 1;
	print_the_output(ecmd, i);
	core->exit_code = 0;
	if (count_n <= 0 || count_n == 2)
		printf("\n");
	return (0);
}
