/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:48:28 by marvin            #+#    #+#             */
/*   Updated: 2024/02/08 18:48:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_AST_P	*init_ast(int type)
{
	t_AST_P	*ast;

	ast = (t_AST_P *)ft_calloc(1, sizeof(t_AST_P));
	ast->type = type;

	return (ast);
}
