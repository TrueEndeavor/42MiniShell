/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:12:19 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/18 11:53:42 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *free_quotes(char **str, char **name, char **var)
{
    int i;

    i = 0;
    printf ("got to free quotes huh..\n");
    if (*str)
    {
        printf ("freeing str:-%s-\n", *str);
        free (*str);
        printf("freed\n");
    }
    if (name)
    {
        printf ("there is name here\n");
        while ((name[i]) != NULL)
        {
            printf ("freeing name:-%s-\n", name[i]);
            free((name)[i]);
            printf("freed\n");
            i++;
        }
        printf("freeing name pointer\n");
        free(name);
        printf("freed\n");
    }
    i = 0;
    if (var)
    {
        printf ("there is var here\n");
        while ((var[i]) != NULL)
        {
            printf ("freeing var:-%s-\n", var[i]);
            free(var[i]);
            printf("freed\n");
            i++;
        }
        printf("freeing var pointer\n");
        free(var);
        printf("freed\n");
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

void    ft_initialize_tab(char **name, char **var)
{
    int i;
    
    i = 0;
    while (i < 10)
    {
        name[i] = NULL;
        var[i] = NULL;
        i++;
    }
}