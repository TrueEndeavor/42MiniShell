/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:12:19 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/25 11:02:04 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_quotes(char **str, char **name, char **var)
{
	int	i;

	i = 0;
	if (*str)
		free (*str);
	if (name)
	{
		while ((name[i]) != NULL)
		{
			free((name)[i]);
			i++;
		}
		free(name);
	}
	i = 0;
	if (var)
	{
		while ((var[i]) != NULL)
		{
			free(var[i]);
			i++;
		}
		free(var);
	}
	return (NULL);
}

char	*dupl(const char *src)
{
	char	*new;
	size_t	len;

	if (!src)
	{
		return (NULL);
	}
	len = ft_strlen(src) + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	if (ft_strlcpy(new, src, len) >= len)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	ft_initialize_tab(char **name, char **var)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		name[i] = NULL;
		var[i] = NULL;
		i++;
	}
}

int	ft_slen(const char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != 0)
			i++;
	}
	return (i);
}
void	ft_ini(int *i, int *var_count, int *i_var)
{
	(*i) = 0;
	(*var_count) = 0;
	(*i_var) = 0;
}