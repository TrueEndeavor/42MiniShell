/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:08:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/31 21:08:31 by lannur-s         ###   ########.fr       */
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

int	fork1(void)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}
