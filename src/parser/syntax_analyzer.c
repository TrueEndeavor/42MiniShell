/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:06:36 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/03 10:18:13 by lannur-s         ###   ########.fr       */
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

/* State Transition Diagram (STT)
/--------------------------------\
| State | Condition | Next State |
|-------|-----------|------------|
|  q0   |   word    |     q1     |
|  q0   |   redir   |     q2     |
|  q1   |   word    |     q1     |
|  q1   |   pipe    |     q3     |
|  q1   |   redir   |     q2     |
|  q2   |   word    |     q1     |
|  q3   |   word    |     q1     |
|  q3   |   redir   |     q2     |
/--------------------------------\ */
t_state_enum	transition(t_state_enum state, t_token_type_E token_type)
{
	if (state == STATE_Q0)
	{
		if ((token_type == T_WORD) || (token_type == T_NAME))
			return (STATE_Q1);
		return (STATE_ERROR);
	}
	if (state == STATE_Q1)
	{
		if ((token_type == T_WORD) || (token_type == T_NAME))
			return (STATE_Q1);
		if (token_type == T_PIPE)
			return (STATE_Q3);
		if ((token_type == T_REDIRECT_IN) || \
			(token_type == T_REDIRECT_OUT) || \
			(token_type == T_HEREDOC) || \
			(token_type == T_APPEND_OUT))
			return (STATE_Q2);
		return (STATE_ERROR);
	}
	if (state == STATE_Q2)
	{
		if ((token_type == T_WORD) || (token_type == T_NAME))
			return (STATE_Q1);
		return (STATE_ERROR);
	}
	if (state == STATE_Q3)
	{
		if ((token_type == T_WORD) || (token_type == T_NAME))
			return (STATE_Q1);
		if ((token_type == T_REDIRECT_IN) || \
			(token_type == T_REDIRECT_OUT) || \
			(token_type == T_HEREDOC) || \
			(token_type == T_APPEND_OUT))
			return (STATE_Q2);
	return (STATE_ERROR);
	}
	return (state);
}

/* Passing the copy of the token pointer, at the end of this function, the 
   tokens pointer will point to the end of the list.
   But don't worry, it wouldn't change anything to the calling function
   which is display_prompt/parse_cmd.
   Ok, let's go.
*/
bool	syntax_analyzer(t_token_T *tokens)
{
	t_token_T	*current;
	t_state_enum	state;

	if (current == NULL)
	{
		ft_printf("Token list empty\n");
		return ;
	}
	current = tokens;
	state = STATE_Q0;
	while (current != NULL)
	{
		if (state != STATE_ERROR)
			state = transition(state, current->type);
		else
		{
			printf("Syntax error\n");
			return (false);
		}
		printf("state changed to:", state);
		current = current->next;
	}
	return (true);
}
