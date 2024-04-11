/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:48:35 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/24 16:49:34 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int			match_builtin(t_cmd_P *root, t_core_struct *core, char *prompt);

int			builtin_cd(t_execcmd_P *ecmd, t_core_struct *core);
int			builtin_echo(t_execcmd_P *ecmd, t_core_struct *core);
int			builtin_env(t_execcmd_P *ecmd, t_core_struct *core);
int			builtin_exit(t_execcmd_P *ecmd, t_core_struct *core, char *prompt);
int			builtin_export(t_execcmd_P *ecmd, t_core_struct *core);
int			builtin_pwd(t_execcmd_P *ecmd, t_core_struct *core);
int			builtin_unset(t_execcmd_P *ecmd, t_core_struct *core);

int			count_of_env(char **envp);
void		display_env_from_array(int count, char	**envp);
void		display_env_from_list(t_env_list *env_list, int is_export);
char		**convert_env_to_stringarray(t_env_list *env_list);
t_env_list	*init_env(char **envp);
void		set_env(t_core_struct *core, char *key_value_pair);
char		*get_env(t_core_struct *core, char *key_to_search);
bool		contains_only_char(char *str, char c);

char		*get_key(char *s);
char		*get_value(char *s);

t_env_list	*ft_lstnew_env(char *name, char *value);
void		ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void		ft_lstclear_env(t_env_list **lst, void (*del)(void *));
void		ft_lstdelone_env(t_env_list *lst, void (*del)(void *));
t_env_list	*ft_lstlast_env(t_env_list *lst);
int			ft_lstsize_env(t_env_list *lst);

t_env_list	*sort_env_list(t_env_list *env_list);
t_env_list	*deep_copy_env(t_env_list *env_list);
t_env_list	*get_node(t_core_struct *core, char *key_to_search);
t_env_list	*get_previous_node(t_core_struct *core, char *key_to_search);
void		get_trimmed_val(char **value_to_set, char *key_value_pair);

#endif