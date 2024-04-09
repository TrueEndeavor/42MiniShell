/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:16:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 08:51:26 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_expand_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*get_end_variable(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] && !valid_expand_char(input[i]))
			break ;
		i++;
	}
	return (input + i);
}

static t_expand_var	*get_variable(t_core_struct *core, char *input)
{
	t_expand_var	*var;

	var = malloc(sizeof(t_expand_var));
	if (!var)
		return (NULL);
	var->end = get_end_variable(input);
	var->name = ft_substr(input, 0, var->end - input);
	var->value = get_env(core, var->name);
	return (var);
}

static void	expand_last_status(t_expand_str *expand, t_core_struct *core)
{
	char	*last_status;

	last_status = ft_itoa(core->exit_code);
	expand->result_size += ft_strlen(last_status);
	expand->result = ft_realloc(expand->result, expand->result_size);
	ft_strlcpy(expand->result + expand->i, last_status, ft_strlen(last_status)
		+ 1);
	expand->i += ft_strlen(last_status);
	expand->input++;
	free(last_status);
}

void	handle_dollar(t_expand_str *expand, t_core_struct *core)
{
	t_expand_var	*var;

	var = get_variable(core, ++expand->input);
	if (var->value)
	{
		expand->result_size += ft_strlen(var->value);
		expand->result = ft_realloc(expand->result, expand->result_size);
		ft_strlcpy(expand->result + expand->i, var->value, ft_strlen(var->value)
			+ 1);
		expand->i += ft_strlen(var->value);
		expand->input += ft_strlen(var->name);
	}
	else
	{
		if (*expand->input == '?')
			expand_last_status(expand, core);
		else if (ft_strlen(var->name) == 0 && expand->state & EX_DOUBLE_QUOTE)
		{
			expand->result = ft_realloc(expand->result, ++expand->result_size);
			expand->result[expand->i++] = '$';
		}
		else
			expand->input = var->end;
	}
	free_expand_var(var);
}
