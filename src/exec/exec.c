/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:25:40 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/11 12:25:45 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execute(char **cmd, char **envp)
{
	char	*path;
	
 	path = NULL;
	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			if (errno == EACCES) 
            {
	            printf("Permission denied\n");
	            exit(126);
	        }
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	path = ft_get_path(cmd[0], envp);
	printf ("path is:-%s-\n", path);
	if (path == NULL)
	{
		//printf ("got here\n");
		//ft_free(path, NULL);
		//return (127);
		printf("%s: command not found\n", cmd[0]);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		//printf ("got there\n");
		//ft_free(path, NULL);
		//printf("execve failed\n");
        if (errno == EACCES) 
        {
            printf("Permission denied\n");
            exit(126);
        }		
		perror("execve");
		exit(EXIT_FAILURE);
	}
	//printf ("E\n");
	return (1); 
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
