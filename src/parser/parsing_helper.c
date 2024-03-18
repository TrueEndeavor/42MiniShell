/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:16:10 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/18 12:12:39 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_expand(t_core_struct *core, char **file_name)
{
    char *ret;

    ret = ft_strdup(get_env(core, (*file_name)));
    free(*file_name);
    return (ret);
}

char    *ft_here(char **value)
{
    char *ret;

    ret = ft_strjoin("$", (*value));
    free(*value);
    return (ret);
}