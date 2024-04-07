/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:06:36 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/07 15:26:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This syntax analyzer verifies if the list of tokens conform to the
grammar of minishell.

*/
/*
				WORD              REDIR
                  --   -------------------------------
                 |  |  |                             |
  *****          |  v  |                             v
 *     *          ******           ------           ------
*       * WORD   *      *  PIPE   /      \  REDIR  /      \ 
*  Q0   * ----->*   Q1   * ----->|   Q3   | ----->|   Q2   |
*       *        *      * <-----  \      /         \      /
 *     *          ******   WORD    ------           ------
  *****           ^                                 |  ^
	|			  |         WORD                    |  |
	|			  -----------------------------------  |
    ----------------------------------------------------
                            REDIR
*/

t_state_enum	transition(t_state_enum state, t_token_type_E token_type)
{
	if (state == STATE_Q0)
		return (transition_q0(state, token_type));
	if (state == STATE_Q1)
		return (transition_q1(state, token_type));
	if (state == STATE_Q2)
		return (transition_q2(state, token_type));
	if (state == STATE_Q3)
		return (transition_q3(state, token_type));
	return (state);
}

bool	handle_syntax_error(t_core_struct *core, t_token_T *token)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n", \
		token_type_to_symbol(token->type));
	core->exit_code = 2;
	return (false);
}

/* Passing the copy of the token pointer, at the end of this function, the 
   tokens pointer will point to the end of the list.
   But don't worry, it wouldn't change anything to the calling function
   which is display_prompt/parse_cmd.
   Ok, let's go.
*/
bool	syntax_analyzer(t_core_struct *core)
{
	t_token_T		*current;
	t_token_T		*prev;
	t_state_enum	state;

	current = (*core->token_head);
	if (current == NULL)
		return (false);
	prev = NULL;
	state = STATE_Q0;
	while (current != NULL)
	{
		state = transition(state, current->type);
		if (state == STATE_ERROR)
		{
			return (handle_syntax_error(core, current));
		}
		prev = current;
		current = current->next;
	}
	if (state != STATE_Q1)
		return (handle_syntax_error(core, prev));
	return (true);
}
