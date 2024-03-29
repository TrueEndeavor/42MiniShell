/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:25:40 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/27 17:30:13 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_directory(char *path)
{
	int	fd;
	int	i;
	int	is_dir;

	i = 0;
	is_dir = false;
	while (path && path[i])
		if (path[i++] == '/')
			is_dir = true;
	if (!is_dir)
		return (false);
	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (false);
	write(2, path, ft_strlen(path));
	write(2, ": Is a directory\n", 17);
	close(fd);
	return (true);
}

int	ft_execute(char **cmd, char **envp)
{
	char	*path;

	path = NULL;
	if (is_directory(cmd[0]))
		return (126);
	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			if (errno == EACCES)
			{
				ft_printf(" Permission denied\n");
				return (126);
			}
			perror("execve");
			return (EXIT_FAILURE);
		}
	}
	path = ft_get_path(cmd[0], envp);
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", cmd[0]);
		return (127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		if (errno == EACCES)
		{
			ft_printf(" Permission denied\n");
			return (126);
		}
		perror("execve");
		return (EXIT_FAILURE);
	}
	return (0);
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
