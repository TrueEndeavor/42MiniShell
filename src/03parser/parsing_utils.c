/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:44:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 10:34:31 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assignment_word(char *str)
{
	char	*position;
	int		len;
	int		index;

	index = 0;
	position = ft_strrchr(str, '=');
	if (position)
		index = position - str;
	len = ft_strlen(str);
	if (index == (len - 1))
		return (true);
	return (false);
}

char	*ft_ex_here(char **str)
{
	char	*ret;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 1;
	ret = NULL;
	c = (*str)[0];
	ret = malloc (ft_slen((*str)) * sizeof (char));
	if (!ret)
		return ((*str));
	while ((*str)[j] != c)
	{
		ret[i] = (*str)[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	free((*str));
	return (ret);
}

int	ft_double_redir(t_token_T *head, int type)
{
	t_token_T	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == type)
			return (1);
		current = current->next;
	}
	return (0);
}

void	ft_here_helper(t_core_struct *c, t_cmd_P **m, t_token_T *t)
{
	(void)c;
	(void)m;
	if ((t)->type == T_VARIABLE)
		(t)->value = ft_here(&(t)->value);
	else if (ft_strcmp ((t)->value, "\"\"") == 0)
	{
		free((t)->value);
		(t)->value = ft_strdup("");
	}
	else if (ft_slen((t)->value) != 0 && (t)->value[0] == '\"')
		(t)->value = ft_ex_here(&(t)->value);
}

t_cmd_P	*mul(t_cmd_P **ch, t_herecmd_P **h, t_redircmd_P **r, int *i)
{
	t_cmd_P *ret;
	
	while ((*ch)->type == REDIR_CMD || (*ch)->type == HERE_CMD)
	{
		if ((*ch)->type == REDIR_CMD)
		{
			(*r) = (t_redircmd_P *) (*ch);
			(*ch) = (*r)->cmd;
			ret = (t_cmd_P *)(*r);
			*i+=1;
		}
		if ((*ch)->type == HERE_CMD)
		{
			(*h) = (t_herecmd_P *) (*ch);
			(*ch) = (*h)->cmd;
			ret = (t_cmd_P *)(*h);
			*i+=1;
		}
	}
	return (ret);
}

/*
In ft_fill_exec

cmd->argv[(*argc)] = (*core->token_head)->value;
to be changed to
add_to_argv(ecmd, (*core->token_head)->value);
*/

/*
void	add_to_argv(t_execcmd_P *ecmd, char *arg)
{
	char	**new_argv;
	int	i;

	i = 0;
	ecmd->argc++;
	new_argv = malloc(cmd->argc * sizeof(char *));
	if (new_argv == NULL)
			return (NULL);
	while (i < ecmd->argc - 1)
	{
			new_argv[i] = cmd->argv[i];
			i++;
	}
	new_argv[argc - 1] = ft_strdup(arg);
	free(ecmd->argv);
	ecmd->argv = new_argv;
}
*/

/*
void free_argv(t_execcmd_P *ecmd)
{
		int	i;

		i = 0;
		while (i < ecmd->argc)
		{
				free(ecmd->argv[i]);
		}
		free(ecmd->argv);
		free(ecmd);
}
*/
