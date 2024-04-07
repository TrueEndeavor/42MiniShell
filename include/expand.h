/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:12:10 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/07 16:12:10 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"
# include "parser.h"

typedef enum e_expand_state
{
	EX_NONE = (1U << 0),
	EX_SINGLE_QUOTE = (1U << 1),
	EX_DOUBLE_QUOTE = (1U << 2),
}					t_expand_state;

typedef struct s_expand_str
{
	char			*result;
	size_t			result_size;
	char			*input;
	size_t			input_size;
	int				i;
	unsigned int	state;
}					t_expand_str;

typedef struct s_expand_var
{
	char			*name;
	char			*value;
	char			*end;
}					t_expand_var;

void				expand_variables(t_token_T **lst, t_core_struct *core);
t_token_T			*delete_expand_node(t_token_T **lst, t_token_T *to_delete);
void				free_expand_var(t_expand_var *var);
void				copy_and_increment(t_expand_str *expand);
void				change_state(unsigned int new_state, t_expand_str *expand);
void				handle_dollar(t_expand_str *expand, t_core_struct *core);

#endif