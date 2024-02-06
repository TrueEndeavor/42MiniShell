/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:23:02 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/06 11:26:55 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_error(char *str)
{
	write(1, "[ERROR] ", 8);
	ft_putstr_fd(str, 2);
	write(1, "\n", 1);
	return (0);
}

void	panic(char *str)
{
	ft_putstr_fd(str, 2);
	exit (1);
}
