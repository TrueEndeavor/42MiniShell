/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:03:48 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/11 14:28:27 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

t_token_T	*init_token(char *value, int type);
char		*token_type_to_str(int type);
char		*token_to_str(t_token_T *token);
char		*token_type_to_str(int type);
char		*token_type_to_symbol(int type);

#endif