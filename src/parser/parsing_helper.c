/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:16:10 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/12 13:27:49 by trysinsk         ###   ########.fr       */
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