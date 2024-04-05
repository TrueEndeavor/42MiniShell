/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/05 03:42:35 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_variable(char *ret, char *var, int i)
{
	int	j;

	j = 0;
	if (var != NULL)
	{
		while ((var)[j] != '\0')
		{
			(ret)[i] = (var)[j];
			i++;
			j++;
		}
	}
	return ;
}

char	*get_name(char *str, int i)
{
	char		*ret;
	char		*copy;
	size_t		new_size;

	i++;
	ret = ft_calloc(1, sizeof(char));
	ret[0] = '\0';
	while (str[i] != '\0' && ((ft_isalnum(str[i])) || str[i] == '_'))
	{
		new_size = ft_strlen(ret) + 2;
		copy = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(copy, ret, new_size);
		free(ret);
		ret = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(ret, copy, new_size);
		ret[new_size - 2] = str[i];
		ret[new_size - 1] = '\0';
		free(copy);
		i++;
	}
	return (ret);
}

int	fill_values(char **str, char **name, char **var, t_core_struct *core)
{
	int	i;
	int	i_var;
	int	var_count;

	var_count = 0;
	i_var = 0;
	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$' && (*str)[i + 1] != ' ' && (*str)[i + 1] != '\"')
		{
			if (DEBUG)
				printf ("next char: -%c-\n", (*str)[i + 1]);
			
			name[i_var] = NULL;
			var[i_var] = NULL;
			name[i_var] = get_name(*str, i);
			i += (int)ft_strlen(name[i_var]);
			var[i_var] = dupl(get_env(core, name[i_var]));
			i_var++;
			var_count++;
		}
		i++;
	}
	return (var_count);
}

void	in_single_quote(int *var_count, char **str, char *ret, int *i, int *i_var)
{
	while ((*str)[*var_count] != '\0')
	{
		if ((*str)[*var_count] == '\'')
		{
			//(*var_count)++;
			break ;
		}
		else if ((*str)[*var_count] == '$')
			(*i_var)++;
		ret[*i] = (*str)[*var_count];
		(*i)++;
		(*var_count)++;
	}
}

void    in_double_quote(int *var_count, char **str, char **name, char **var, char *ret, int *i, int *i_var)
{
	while ((*str)[*var_count] != '\0')
	{
		if ((*str)[*var_count] == '\"')
		{
			//(*var_count)++;
			#if DEBUG
			printf("I break here\n");
			#endif
			break ;
		}
		else if ((*str)[*var_count] == '$' && (*str)[*var_count + 1] != ' ' && (*str)[*var_count + 1] != '\"')
		{
			copy_variable(ret, var[*i_var], *i);
			*i += ft_slen(var[*i_var]);
			*var_count += (ft_slen(name[*i_var]));
			#if DEBUG
			dprintf(1, "after replacing, var_count is set on this char........=%c\n", (*str)[*var_count]);
			#endif
			(*i_var)++;
		}
		else
		{
			ret[*i] = (*str)[*var_count];
			(*i)++;
		}
		(*var_count)++;
	}   
}
void	fill_string(char **str, char **name, char **var, char *ret)
{
	int	i;
	int	var_count;
	int	i_var;

	i = 0;
	var_count = 0;
	i_var = 0;
	while ((*str)[var_count] != '\0')
	{
		#if DEBUG
		printf("next char = (*str)[var_count]=%c\n", (*str)[var_count]);
		#endif
		if ((*str)[var_count] == '\'')
		{
            var_count++;
			in_single_quote((&var_count), str, ret, &i, &i_var);
			if ((*str)[var_count] == '\0')
				break ;
		}
		else if ((*str)[var_count] == '\"')
		{
			var_count++;
			in_double_quote(&var_count, str, name, var, ret, &i, &i_var);
			#if DEBUG
			printf("after break  = (*str)[var_count]=%c\n", (*str)[var_count]);
			#endif
			if ((*str)[var_count] == '\0')
				break ;
		}
		else if ((*str)[var_count] == '$' && (*str)[var_count + 1] != ' ' && (*str)[var_count + 1] != '\"')
		{
			ret[var_count] = '$';
			copy_variable(ret, var[i_var], i);
			i += ft_slen(var[i_var]);
			var_count += (ft_slen(name[i_var]));
			#if DEBUG
			dprintf(1, "after replacing, var_count is set on this char........=%c, %s\n", (*str)[var_count], ret);
			#endif
			i_var++;
		}
		else
		{
			ret[i] = (*str)[var_count];
			i++;
		}
		var_count++;
	} 
	ret[i] = '\0';
	dprintf(1, "after replacing,the string is........, %s\n", ret);
}

char	*quote(char **s, t_core_struct *co, int var_c, int i)
{
	char	*ret;
	char	**name;
	char	**var;
	int		size;
	
	size = check_num_arg((*s));
	name = malloc(size * sizeof(char *));
	var = malloc(size * sizeof(char *));
	ft_initialize_tab(name, var, size);
	var_c = fill_values(s, name, var, co);
	if (var_c == -1)
		return (free_quotes(s, name, var));
	size = (int)ft_strlen(*s);
	i = 0;
	while (var_c != 0)
	{
		size += ft_slen(var[i]);
		size -= (ft_slen(name[i]) + 1);
		i++;
		var_c--;
	}
	ret = malloc ((size + 1) *(sizeof(char)));
	fill_string(s, name, var, ret);
	free_quotes(s, name, var);
	return (ret);
}
