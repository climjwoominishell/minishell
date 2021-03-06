/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:42:45 by jwoo              #+#    #+#             */
/*   Updated: 2021/08/14 11:39:09 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include "libft/libft.h"

# define NONE 0
# define REDIRECT1 1
# define REDIRECT2 2
# define REDIRECT3 3
# define REDIRECT4 4
# define PIPE 5

int	g_status;

typedef struct s_quote
{
	int	q_single;
	int	q_double;
	int	q_single_index;
	int	q_double_index;
	int	q_remain_single;
	int	q_remain_double;
}	t_quote;

typedef struct s_envp
{
	char	**envp_list;
	int		*sort_idx;
}	t_envp;

typedef struct s_fd
{
	int		**pipe_fds;
	int		size;
	int		idx;
	int		current_idx;
	int		*fd;
}	t_fd;

typedef struct s_cmd
{
	t_list	*current_cmd;
	t_list	*argument;
	t_list	*command;
	t_list	*first_cmd;
	char	**append_cmd;
}	t_cmd;

void	init_quote(t_quote *quote);
int		is_remain_quote(char *line, int idx, char quote);
void	valid_or_invalid_quote(char *line, int idx, t_quote *quote);
void	check_quote(char *line, t_quote *quote);

int		env_validation(char *name);
void	envp_add(t_envp *envp_, char *content);
int		export_without_arg(char **arg_arr);

int		atoi_sign(char *str);
int		ft_atoi(char *str, int *integer);

void	ft_lstclear_two(t_list **lst, void (*del)(char **));

int		factor_num(char *s);
char	**factor_len(char **factor, char *s, int factor_num);
void	factor_split(char **factor, char *s, int factor_num);
void	free_two_dimension(char **word);
char	**ft_split_space(char *s);

int		get_arg_size(char **arg);
char	*str_append_char(char *str, char c);
char	**append_strarr(char **str1, char **str2);

char	*strjoin_exception_case(char *s1, char *s2);
void	free_strjoin_arg(char **s1, char **s2);
char	*ft_strjoin_with_free(char *s1, char *s2);

void	arr_swap(int *arr, int i, int j);
void	sort_envp_idx(t_envp *envp);
void	init_envp_status(t_envp *envp, char **first_envp);

int		is_not_bulitin(char **arg_arr, t_envp *envp, bool is_parent);
int		interpret_with_pipe(char **arg_arr, t_envp *envp);
int		interpret_without_pipe(char **arg_arr, t_envp *envp);

int		free_ret(char **str, int ret);
char	**get_env_ptr(char *key, char **envp);
int		mini_cd(char **arg, t_envp *envp);

int		mini_echo(char **arg_arr);
int		mini_env(char **arg, t_envp *envp);
int		mini_exit(char **arg_arr, bool is_parent);

void	print_export(t_envp *envp);
void	with_eq(char **arg_arr, t_envp *envp, int i);
void	without_eq(char **arg_arr, t_envp *envp, int i);
int		print_export_err(char *arg);
int		mini_export(char **arg_arr, t_envp *envp);

int		mini_pwd(void);

int		get_flag(t_envp *envp, char **arg, int i);
void	unset_var(t_envp *envp, int flag);
int		print_unset_err(char *arg);
int		mini_unset(char **arg, t_envp *envp);

int		valid_quote(char **arg, char *line, t_quote *quote, int *i);
void	invalid_quote(char **arg, char *line, int *i);
t_list	*arg_to_list(char *line, t_quote *quote);

int		with_path(char **arg_arr, t_envp *envp);
int		exec_file(char **path, char **arg_arr, t_envp *envp);
int		without_path(char **arg_arr, t_envp *envp);

int		get_file_type(char *path);
int		print_file_dir_err(char *arg, char **slash, int type);
int		get_type(int first_slash, char **slash, int *i);
int		file_or_directory(char *arg);

int		is_separate(char *command);
int		get_unit_size(t_list *arg_list);
void	add_one_unit_cmd(t_list **arg_list, t_list **cmd_list, char	**arg_arr);
void	add_one_line_of_cmd(t_list **arg_list, t_envp *envp, t_list **cmd_list);
t_list	*list_to_char_arr(t_list *arg_list, t_envp *envp);

char	*parse_path(t_envp *envp);
int		get_last_slash_idx(char *arg);

int		in_single_quote(char **ret, char *cmd_line, int i);
int		in_double_quote(char **ret, char *cmd_line, int i, t_envp *envp);
int		without_quote_env(char **ret, char *cmd_line, int i);
int		find_env(char **ret, char *cmd_line, int i, t_envp *envp);
char	*remove_quote(char *cmd_line, t_envp *envp);

int		get_equal_idx(char *env_line);
char	*get_value(char *key, char **envp);
void	replace_env_value(char *key, char **ret, t_envp *envp);
int		is_valid_env(char *cmd_line, int i);
char	*get_path(char **env_path, char *arg);

void	sigint_handler(int signo);
void	child_handler(int signo);
void	redirect_handler(int signo);
void	set_child_signal(void);
void	set_signal(void);

void	free_fd(t_fd *fd);
void	free_cmd(t_cmd *cmd);
void	free_cmd_fd(t_cmd *cmd, t_fd *fd);
int		free_error_file_ret(char **error_file);

void	handle_simple(t_fd *fd, t_cmd *cmd, t_envp *envp);
void	handle_line(char **line_prompt, t_cmd *cmd, t_envp *envp, t_fd *fd);

int		print_pipe_err(void);
int		pipe_parent(t_fd *fd);
int		handle_pipe(t_cmd *cmd, t_fd *fd, t_envp *envp);

int		output_redirect(t_cmd *cmd, t_fd *fd, char **redirect_cmd);
int		input_redirect(t_cmd *cmd, t_fd *fd, char **redirect_cmd, \
		char **error_file);
void	eof_child(t_fd *fd, char **redirect_cmd);
int		eof_redirect(t_cmd *cmd, t_fd *fd, char **redirect_cmd, \
		char **error_file);
int		redirect_case(t_cmd *cmd, t_fd *fd, char **redirect_cmd, \
		char **error_file);

char	*to_sperate(int num);
int		is_redirection(int flag);
int		redir_err(char *error_file, t_cmd *cmd);
void	append_cmd(t_cmd *cmd, char **redirect_cmd);
int		handle_redirect(t_cmd *cmd, t_fd *fd);

void	init_fd(t_fd *fd, t_list *cmd);
void	init_cmd(char *line, t_cmd *cmd, t_envp *envp, t_quote quote);
void	set_fd_cmd(t_fd *fd, t_cmd *cmd);

char	*make_prompt(void);
void	minishell(char **first_envp);

#endif