/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:26 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/11 11:16:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_exec(t_core_struct *core, int *argc, t_execcmd_P *cmd)
{
	cmd->argv[(*argc)] = (*core->token_head)->value;
	(*argc)++;
	if ((*argc) >= MAXARGS)
		panic("too many args");
	*core->token_head = advance_token(core->token_head);
}

void	copy_variable(char *ret, char *var, int i)
{
	int	j;

	j = 0;
	if (var != NULL)
	{
		while ((var)[j] != '\0')
		{
			(ret)[i] = (var)[j];
			i++;
			j++;
		}
	}
	return ;
}

char	*get_name(char *str, int i)
{
	char		*ret;
	char		*copy;
	size_t		new_size;

	i++;
	ret = ft_calloc(1, sizeof(char));
	ret[0] = '\0';
	while (str[i] != '\0' && ((ft_isalnum(str[i])) || str[i] == '_'))
	{
		new_size = ft_strlen(ret) + 2;
		copy = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(copy, ret, new_size);
		free(ret);
		ret = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(ret, copy, new_size);
		ret[new_size - 2] = str[i];
		ret[new_size - 1] = '\0';
		free(copy);
		i++;
	}
	return (ret);
}
