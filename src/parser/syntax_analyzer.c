/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:06:36 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/01 11:25:35 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Passing the copy of the token pointer, at the end of this function, the 
   tokens pointer will point to the end of the list.
   But don't worry, it wouldn't change anything to the calling function
   which is display_prompt, just before calling the parse_cmd.
   Ok, let's go.
*/
bool	syntax_analyzer(t_token_T *tokens)
{
	t_token_T	*current;

	if (current == NULL)
	{
		ft_printf("Token list empty\n");
		return ;
	}
	current = tokens;
	while (current != NULL)
	{
		//do something
		// token->type, token->value
		current = current->next;
	}
	//if something bad
	return (false);

	//if all good
	return (true);
}