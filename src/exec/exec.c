/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:25:40 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 10:57:02 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_execute(char **cmd, char **envp)
{
	char	*path;

	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			ft_free(NULL, cmd);
			ft_error("execve failed\n");
		}
	}
	path = ft_get_path(cmd[0], envp);
	if (!path)
	{
		ft_free(path, cmd);
		ft_error("PATH not found\n");
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(path, cmd);
		ft_error("execve failed\n");
	}
}

char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	**possible_paths;
	char	*path;
	char	*complete_path;

	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	possible_paths = ft_split(path, ':');
	i = 0;
	while (possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i++], "/");
		complete_path = ft_strjoin(path, cmd);
		free (path);
		if (access(complete_path, F_OK) == 0)
			return (complete_path);
		free(complete_path);
	}
	ft_free(NULL, possible_paths);
	return (NULL);
}

void	ft_free(char *path, char **cmd)
{
	int	i;

	i = 0;
	if (path)
		free(path);
	if (*cmd)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

