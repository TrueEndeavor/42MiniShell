/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/11 12:25:18 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    copy_variable(char *ret, char *var, int i)
{
    int j;

    j = 0;
    while ((var)[j] != '\0')
    {
        (ret)[i] = (var)[j];
        i++;
        j++;
    }
    return ;
}

char    *get_name(char *str, int i)
{
    char *ret;
    int     i_name;
	char		*new_value;    
	int			new_size;    

    i_name = 0;
    i++;
    ret = ft_calloc(1, sizeof(char));
	ret[0] = '\0';
    while (str[i] != '\0' && ((ft_isalnum(str[i])) || str[i] == '_'))
    {
        new_size = ft_strlen(ret) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
        ret[i_name] = str[i];
        ret[i_name + 1] = '\0';
        i_name++;
        i++;
    }
    ret[i_name] = '\0';
    return (ret);
}

int     fill_values(char **str, char **name, char **var, t_core_struct *core)
{
    int     i;
    int     i_var;
    int     var_count;
    char    *temp;

    printf ("begining of fill_values\n");
    var_count = 0;
    i_var = 0;
    i = 0;
    while ((*str)[i] != '\0')
    {
        if ((*str)[i] == '$')
        {
            name[i_var] = malloc(1 * sizeof(char *));
            var[i_var] = malloc(1 * sizeof(char *));
            name[i_var] = get_name(*str, i);
            i += (int)ft_strlen(name[i_var]);
            temp = duplicate(get_env(core, name[i_var]));
            printf ("temp: -%s-\n", temp);
            printf ("got here huh....\n");
            var[i_var] = temp;
            //var[i_var] = ft_strdup(get_env(core, name[i_var]));
            printf ("finaly huh....\n");
            if (var[i_var] == NULL)
                return (-1);
            i_var++;
            var_count++;
        }
        i++;
    }
    printf ("end of fill_values\n");
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
            i+= ((int)ft_strlen(var[i_var]));
            var_count+= ((int)ft_strlen(name[i_var]) + 1);
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

    name = malloc(1 * sizeof(char *));
    var = malloc(1 * sizeof(char *));
    var_count = fill_values(str, name, var, core);
    if (var_count == -1)
        return (free_quotes(str, name, var));
    size = (int)ft_strlen(*str);
    i_var = 0;
    while (var_count != 0)
    {
        size += ft_strlen(var[i_var]);
        size -= (ft_strlen(name[i_var]) + 1);
        i_var++;
        var_count--;
    }
    ret = malloc ((size + 1) *(sizeof(char)));
    fill_string(str, name, var, ret);
    free_quotes(str, name, var);
    return (ret);
}

/*char    *quote_string(char **str, t_core_struct *core)
{
    char    *ret;
    char    **name;
    char    **var;
    int i_var;
    int var_count;
    int i;
    int size;
    
    var = NULL;
    name = NULL;
    var_count = 0;
    i_var = 0;
    i = 0;
    name = malloc(1 * sizeof(char *));
    var = malloc(1 * sizeof(char *));
    while (i < (int)ft_strlen(*str))
    {
        if ((*str)[i] == '$')
        {
            name[i_var] = malloc(1 * sizeof(char *));
            var[i_var] = malloc(1 * sizeof(char *));
            name[i_var] = get_name(*str, i);
            i += (int)ft_strlen(name[i_var]);
            var[i_var] = get_env(core, name[i_var]);
            if (var[i_var] == NULL)
                return (NULL);
            i_var++;
            var_count++;
        }
        i++;
    }    
    i_var = 0;
    size = (int)ft_strlen(*str);
    while (var_count != 0)
    {
        size += ft_strlen(var[i_var]);
        size -= (ft_strlen(name[i_var]) + 1);
        i_var++;
        var_count--;
    }
    ret = malloc ((size + 1) *(sizeof(char)));
    i = 0;
    i_var = 0;
    while ((*str)[var_count] != '\0')
    {
        printf ("current char: %c\n", (*str)[var_count]);
        if ((*str)[var_count] == '$')
        {
            copy_variable(ret, var[i_var], i);
            i+= ((int)ft_strlen(var[i_var]));
            var_count+= ((int)ft_strlen(name[i_var]) + 1);
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
    free(*str);
    return (ret);
}*/
