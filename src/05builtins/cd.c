/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 12:44:40 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_env_list *pwd, t_env_list *old_pwd)
{
	if (pwd != NULL)
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
}

int	check_cd(t_execcmd_P *ecmd, t_core_struct *core)
{
	if (ecmd->argv[2] != NULL)
	{
		ft_printf(" too many arguments\n");
		core->exit_code = 1;
		return (core->exit_code);
	}
	return (0);
}

int	builtin_cd(t_execcmd_P *ecmd, t_core_struct *core)
{
	t_env_list	*old_pwd;
	t_env_list	*pwd;

	if (check_cd(ecmd, core) == 1)
		return (1);
	old_pwd = get_node(core, "OLDPWD");
	pwd = get_node(core, "PWD");
	if (ecmd->argv[1] == NULL)
		chdir(get_env(core, "HOME"));
	else if (ft_strcmp(ecmd->argv[1], "-") == 0)
	{
		if (chdir (old_pwd->value) == -1)
			return (1);
	}
	else if (chdir (ecmd->argv[1]) == -1)
	{
		perror("cd");
		core->exit_code = 1;
		return (core->exit_code);
	}
	update_pwd(pwd, old_pwd);
	return (core->exit_code);
}
