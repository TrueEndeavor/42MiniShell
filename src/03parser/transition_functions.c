/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:48:59 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 09:14:16 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_state_enum	transition_q0(t_state_enum state, t_token_type_E token_type)
{
	if ((token_type == T_WORD) || (token_type == T_VARIABLE) || \
		(token_type == T_DOLLAR) || (token_type == T_EXITCODE))
		return (STATE_Q1);
	else if ((token_type == T_REDIRECT_IN) || \
		(token_type == T_REDIRECT_OUT) || \
		(token_type == T_HEREDOC) || \
		(token_type == T_APPEND_OUT))
		return (STATE_Q2);
	else if (token_type == T_LINEBREAK)
		return (state);
	return (STATE_ERROR);
}

t_state_enum	transition_q1(t_state_enum state, t_token_type_E token_type)
{
	if ((token_type == T_WORD) || (token_type == T_VARIABLE) || \
		(token_type == T_DOLLAR) || (token_type == T_EXITCODE))
		return (STATE_Q1);
	else if (token_type == T_PIPE)
		return (STATE_Q3);
	else if ((token_type == T_REDIRECT_IN) || \
		(token_type == T_REDIRECT_OUT) || \
		(token_type == T_HEREDOC) || \
		(token_type == T_APPEND_OUT))
		return (STATE_Q2);
	else if (token_type == T_LINEBREAK)
		return (state);
	return (STATE_ERROR);
}

t_state_enum	transition_q2(t_state_enum state, t_token_type_E token_type)
{
	if ((token_type == T_WORD) || (token_type == T_VARIABLE) || \
		(token_type == T_EXITCODE))
		return (STATE_Q1);
	else if (token_type == T_LINEBREAK)
		return (state);
	return (STATE_ERROR);
}

t_state_enum	transition_q3(t_state_enum state, t_token_type_E token_type)
{
	if ((token_type == T_WORD) || (token_type == T_VARIABLE) || \
		(token_type == T_EXITCODE))
		return (STATE_Q1);
	else if ((token_type == T_REDIRECT_IN) || \
		(token_type == T_REDIRECT_OUT) || \
		(token_type == T_HEREDOC) || \
		(token_type == T_APPEND_OUT))
		return (STATE_Q2);
	else if (token_type == T_LINEBREAK)
		return (state);
	return (STATE_ERROR);
}
