/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/12 19:00:19 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "libft.h"
# include "utils.h"
# include "dev.h"

int		display_error(char *str);
void	panic(char *str);

t_cmd_P	*parse_cmd(t_token_T **token_list);
void	run_cmd(t_cmd_P *cmd);
int		exec(char *path, char **av);

#endif