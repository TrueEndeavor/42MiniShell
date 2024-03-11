/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:12:19 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/11 12:26:10 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *free_quotes(char **str, char **name, char **var)
{
    int i;

    i = 0;
    printf ("got there huh..\n");
    if (*str)
    {
        printf ("freeing str:-%s-\n", *str);
        free (*str);
    }
    if (name)
    {
        while (name[i])
        {
            printf ("freeing name:-%s-\n", name[i]);
            free(name[i]);
            i++;
        }
        free(name);
    }
    i = 0;
    if (var)
    {
        while (var[i])
        {
            printf ("freeing var:-%s-\n", var[i]);
            free(var[i]);
            i++;
        }
        free(var);
    }
    return (NULL);
}

char    *duplicate(const char *src)
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
