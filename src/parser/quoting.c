/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/19 10:09:31 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    copy_variable(char *ret, char *var, int i)
{
    int j;

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

char    *get_name(char *str, int i)
{
    char *ret;
	char		*copy;    
	size_t      new_size;    

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

int     fill_values(char **str, char **name, char **var, t_core_struct *core)
{
    int     i;
    int     i_var;
    int     var_count;

    ft_initialize_tab(name, var);
    var_count = 0;
    i_var = 0;
    i = 0;
    while ((*str)[i] != '\0')
    {
        if ((*str)[i] == '$')
        {
            name[i_var] = NULL;
            var[i_var] = NULL;
            name[i_var] = get_name(*str, i);
            i += (int)ft_strlen(name[i_var]);
            var[i_var] = duplicate(get_env(core, name[i_var]));
            i_var++;
            var_count++;
        }
        i++;
    }
    return (var_count);
}

void    fill_string(char **str, char **name, char **var, char *ret)
{
    int i;
    int var_count;
    int i_var;

    i = 0;
    var_count = 0;
    i_var = 0;
    while ((*str)[var_count] != '\0')
    {
        if ((*str)[var_count] == '$')
        {
            copy_variable(ret, var[i_var], i);
            i+= ((int)ft_slen(var[i_var]));
            var_count+= ((int)ft_slen(name[i_var]) + 1);
            i_var++;
        }
        else
        {
            ret[i] = (*str)[var_count];
            i++;
            var_count++;
        }
    }
    ret[i] = '\0';
}

char    *quote_string(char **str, t_core_struct *core)
{
    char    *ret;
    char    **name;
    char    **var;
    int     var_count;
    int     size;
    int     i_var;

    name = malloc(10 * sizeof(char *));
    var = malloc(10 * sizeof(char *));
    var_count = fill_values(str, name, var, core);
    if (var_count == -1)
        return (free_quotes(str, name, var));
    size = (int)ft_strlen(*str);
    i_var = 0;
    while (var_count != 0)
    {
        size += ft_slen(var[i_var]);
        size -= (ft_slen(name[i_var]) + 1);
        i_var++;
        var_count--;
    }
    ret = malloc ((size + 1) *(sizeof(char)));
    fill_string(str, name, var, ret);
    free_quotes(str, name, var);
    return (ret);
}
