/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:35:36 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 15:44:15 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	*split_env;
	char	*env_line;
	char	**split_cmd;
	char	**split_cmd1;
	int		pipefd[2];
	int		valid;
	char	**av;
	char	**env;
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	*cmd_loc;
	char	**cmd;
	char	*cmd1_loc;
	char	*cmd2_loc;
	int		**fd;
	int		pid1;
	int		pid2;
	int		ac;
	int		status;
	int		last_status;
	int		*pid;
}			t_data;

typedef struct s_malloc
{
	void	*data;
	void	*next;
}			t_malloc;

void		ft_lstclear(t_malloc **lst);
char		*ft_strjoin(char *s, char *s1, t_malloc **ft);
char		**ft_split_char(char *s, char c);
int			ft_strlen(char *s);
char		*ft_strstr(char *haystack, char *needle);
char		**ft_split_str(char *str, char *charset);
int			count_words(char *s, char c);
char		*ft_strchr(char *str, int c);
void		ft_putstr_fd(char *s, int fd);
void		*ft_malloc(t_malloc **str, int size);
void		ft_init(t_data *pipex, int ac, char **av, char **env);
void		parent_process(t_data *pipex, int *i);
void		close_pipex(t_data *pipex);

//------------child1

void		ft_path(t_data *pipex, char **env);

//--------child2
void		ft_free2(char **tab);
//---------middle

void		get_cmd(t_data *pipex, char *cmd, int i);

//------- bonus

void		ft_pipe(t_data *pipex, int ac);
void		ft_alloc_pipe(t_data *pipex, t_malloc **ft, int ac);
void		close_pipex(t_data *pipex);
void		check_empty(t_data *pipex, char *cmd, int i);
void		get_cmd(t_data *pipex, char *cmd, int i);
int			check_env(t_data *pipex, t_malloc **ft);
int			get_cmd_loc(t_data *pipex, t_malloc **ft);
void		execute_cmd(t_data *pipex, char **env, t_malloc **ft, int i);

void		command_not_found(char *s);
void		command_error(char *s);
void		error_pid(int pid);
void		error_fd1(int fd, t_data *pipex);
void		error_fd2(int fd, t_data *pipex);

void		child1_process(t_data *pipex, int i);
void		child_last_process(t_data *pipex, int i);
void		parent_process(t_data *pipex, int *i);

#endif
