/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/15 16:50:15 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void print_the_output(t_execcmd_P *ecmd, int i)
{
	while (ecmd->argv[i] != NULL)
	{
		if (ft_strcmp(ecmd->argv[i], "-n") != 0)
		{
			ft_printf("%s",ecmd->argv[i]);
			ft_printf("%c", ' ');
		}
		i++;
	}
} */

void print_skipping(t_execcmd_P *ecmd)
{
	int i;
	int j;
	int found_non_n_char;
	int valid_skip_new_line;
	
	i = 1;
	valid_skip_new_line = 0;
	while (ecmd->argv[i] != NULL)
	{
	found_non_n_char = 1;
	//printf("ecmd->argv[i]=...%s...\n",ecmd->argv[i]);
		if ((ecmd->argv[1][0] == '-') && (ecmd->argv[1][1] == 'n'))
		{
			valid_skip_new_line = 1;
		}
		if ((ecmd->argv[i][0] == '-') && (ecmd->argv[i][1] == 'n'))
		{
			found_non_n_char = 0;
			j = 2;
			
			while (ecmd->argv[i][j] != '\0') 
			{
				j++;
				printf("ecmd->argv[i][j]=...%c...\n",ecmd->argv[i][j]);
				if (ecmd->argv[i][j] != 'n')
				{   
					found_non_n_char = 1;
					valid_skip_new_line = 0;
				}
				else
				{
					found_non_n_char = 0;
				}
				j++;
			}
		}
		printf("found_non_n_char=...%d...\n",found_non_n_char);
		if (found_non_n_char)
		{
			ft_printf("%s",ecmd->argv[i]);
			ft_printf("%c", ' ');
		}
		i++;
	}
		printf("valid_skip_new_line=...%d...\n",valid_skip_new_line);	
	if (valid_skip_new_line < 1)
		ft_printf ("\n");
}

/* void print_the_output(t_execcmd_P *ecmd, int i)
{
	while (ecmd->argv[i] != NULL)
	{
		if (ecmd->argv[i][0] == '-' && ecmd->argv[i], "-n") != 0)
		{
			ft_printf("%s",ecmd->argv[i]);
			ft_printf("%c", ' ');
		}
		i++;
	}
} */


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
	
	/* if ((ecmd->argv[1][0] == '-') && (ecmd->argv[1][1] == 'n'))
	{
		if (contains_only_char(ecmd->argv[1], 'n'))
		{
			count_n = 1;
			i++;
		}
	} */
	core->exit_code = 0;
	print_skipping(ecmd);
	//print_the_output(ecmd, i);
	if (count_n < 1)
		ft_printf ("\n");
	(void) core;
	
	return (0);
}
