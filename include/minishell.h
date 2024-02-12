/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/09 09:55:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "AST.h"
# include "exec.h"
# include "libft.h"
# include "utils.h"
# include "dev.h"

int	display_error(char *str);

#endif