/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:57 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/23 11:06:58 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_of_env(char **envp)
{
    int		count;
    
    count =0;
	while (*envp != NULL)
	{
	    if (*envp[0] != '\0')
		    count++;
		envp++;
    }
    return (count);
}

void	display_env(int count, char	**envp)
{
    int i;
    
    i = 1;
    while (i < count)
	{
	    if ((ft_strchr(envp[i], '=')) != NULL)
    		printf("%s\n",envp[i]);
	    i++;
	}
}