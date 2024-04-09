/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:17:23 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 08:50:35 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand_var(t_expand_var *var)
{
	free(var->name);
	free(var);
}

void	copy_and_increment(t_expand_str *expand)
{
	expand->result = ft_realloc(expand->result, expand->result_size + 1);
	*(expand->result + expand->i++) = *expand->input;
	expand->result_size++;
	expand->input++;
}

void	change_state(unsigned int new_state, t_expand_str *expand)
{
	expand->state ^= new_state;
	expand->input++;
}

void	ft_tokdelone(t_token_T *lst, void (*del)(void *))
{
	t_token_T	*tmp;

	tmp = lst;
	if (lst != NULL)
	{
		lst = tmp->next;
		del(&tmp->value);
		free(tmp);
	}
}

t_token_T	*delete_expand_node(t_token_T **lst, t_token_T *to_delete)
{
	t_token_T	*curr;
	t_token_T	*prev;

	curr = *lst;
	prev = NULL;
	while (curr && curr != to_delete)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*lst = to_delete->next;
	else
		prev->next = to_delete->next;
	ft_tokdelone(to_delete, free);
	if (!prev)
		return (*lst);
	return (prev->next);
}
