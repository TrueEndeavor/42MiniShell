/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:45:19 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 09:58:29 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_execcmd_P *ecmd, t_core_struct *core)
{
    if (core->env_list == NULL)
    {
        return (1);
    }
    (void) ecmd;
    display_env_from_list(core->env_list);
    return (0);
}