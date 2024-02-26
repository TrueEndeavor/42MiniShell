/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:45:19 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/26 14:52:04 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_execcmd_P *ecmd, t_core_struct *core)
{
    (void) ecmd;
    display_env_from_list(core->env_list);
    return (0);
}