/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:40:21 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/07 09:43:43 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	print_token_list(t_token_T *token_head)
{
	if (token_head)
	{
		printf("Token type = %d & the value is = %s\n", token_head->type, \
			token_head->value);
		while (token_head->next)
		{
			token_head = token_head->next;
			printf("Token type = %d & the value is = %s\n", token_head->type, \
				token_head->value);
		}
	}
}
