/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/05 16:43:23 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    copy_variable(char **ret, char *var, int i)
{
    int j;

    j = 0;
    while (var[j] != '\0')
    {
        *ret[i] = var[j];
        i++;
        j++;
    }
    return ;
}

char    *get_name(char *str, int i)
{
    char *ret;
    int     i_name;

    ret = NULL;
    i_name = 0;
    i++;

    while (str[i] != '\0' && ((ft_isalnum(str[i])) || str[i] == '_'))
    {
        printf("heyyy...str[i]......%c\n", str[i]);
        ret[i_name] = str[i];
        printf("heyyy...str[i]......%c\n", ret[i_name]);
        i_name++;
        i++;
    }
    ret[i_name] = '\0';
    printf ("end of get name\n");
    return (ret);
}

char    *quote_string(char *str, t_core_struct *core, int quotes)
{
    char    *ret;
    char    **name;
    char    **var;
    int i_var;
    int var_count;
    int i;
    int size;
    
    size = ((int)ft_strlen(str) -2);
    var = NULL;
    name = NULL;
    var_count = 0;
    i_var = 0;
    i = 1;
    while (i < ((int)ft_strlen(str) - 1))
    {
        if (str[i] == '$' && quotes == 2)
        {
            printf ("BOOP\n");
            name[i_var] = get_name(str, i);
            printf ("return boop\n");
            i += (int)ft_strlen(name[i_var]);
            var[i_var] = get_env(core, name[i_var]);
            i_var++;
            var_count++;
        }
        i++;
    }    
    i_var = 0;
    while (var_count > 0)
    {
        size += ft_strlen(var[i_var]);
        size -= ft_strlen(name[i_var]);
        i_var++;
        var_count--;
    }
    ret = malloc ((size + 1) *(sizeof(char)));
    i = 0;
    i_var = 0;
    while ((i + 1) < ((int)ft_strlen(str) - 1))
    {
        if (str[i + 1] == '$' && quotes == 2)
        {
            copy_variable(&ret, var[i_var], i);
            i+= ((int)ft_strlen(var[i_var]));
            i_var++;
        }
        else
        {
            ret[i] = str[i + 1];
        }
        i++;
    }
    ret[i] = '\0';
    free(str);
    return (ret);
}
