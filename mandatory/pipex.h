/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:35:36 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 15:44:31 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	**cmd;
	char	*split_env;
	char	*env_line;
	char	**split_cmd;
	char	**split_cmd1;
	int		pipefd[2];
	int		valid;
	char	**env;
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_loc;
	char	*cmd2_loc;
	int		fd[2];
	int		pid1;
	int		pid2;
	int		status;
}			t_data;

typedef struct s_malloc
{
	void	*data;
	void	*next;
}			t_malloc;

char		*ft_strjoin(char *s, char *s1, t_malloc **ft);
char		**ft_split_char(char *s, char c);
int			ft_strlen(char *s);
char		*ft_strstr(char *haystack, char *needle);
char		**ft_split_str(char *str, char *charset);
int			count_words(char *s, char c);
void		error_pid(int pid);
void		error_fd1(int fd, char **av);
void		error_fd2(int fd, char **av);
void		child1_process(t_data *pipex, char **env, char **av, t_malloc **ft);
void		child2_process(t_data *pipex, char **env, char **av, t_malloc **ft);
char		*ft_strrchr(char *str, int c);
void		ft_putstr_fd(char *s, int fd);
void		*ft_malloc(t_malloc **str, int size);
void		ft_check(t_data *pipex, int ac, char **av, char **env);
void		ft_init(t_data *pipex, int ac, char **av, char **env);
void		parent_process(t_data *pipex);

//------------child1

void		get_cmd1(t_data *pipex, char **av, t_malloc **ft);
int			get_cmd1_loc(t_data *pipex, t_malloc **ft);
void		command_not_found(char *s);
void		command_error(char *s);
void		infile_cmd_process(t_data *pipex, char **av, t_malloc **ft);
void		ft_path(t_data *pipex, char **env);

//--------child2
void		get_cmd2(t_data *pipex, char **av, t_malloc **ft);
int			check_env2(t_data *pipex, t_malloc **ft);
int			get_cmd2_loc(t_data *pipex, t_malloc **ft);
void		outfile_cmd_process(t_data *pipex, t_malloc **ft);
void		ft_free2(char **tab);
void		ft_lstclear(t_malloc **lst);

#endif
