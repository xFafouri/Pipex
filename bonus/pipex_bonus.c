/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:50:22 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 17:55:38 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_path(t_data *pipex, char **env)
{
	int	j;

	j = 0;
	pipex->env = NULL;
	pipex->env_line = NULL;
	while (env[j])
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
		{
			pipex->env_line = ft_strstr(env[j], "PATH=");
			break ;
		}
		j++;
	}
	if (pipex->env_line)
	{
		pipex->env = ft_split_char(pipex->env_line, ':');
	}
	else
	{
		pipex->valid = 1;
		pipex->env = ft_split_char("  ", ':');
	}
}

void	ft_init(t_data *pipex, int ac, char **av, char **env)
{
	pipex->valid = 0;
	pipex->infile = av[1];
	pipex->ac = ac;
	pipex->outfile = av[ac - 1];
	pipex->status = 0;
	pipex->cmd = NULL;
	pipex->cmd_loc = NULL;
	pipex->av = av;
	pipex->av += 2;
	pipex->last_status = 0;
	pipex->status = 0;
	ft_path(pipex, env);
}

void	process(t_data *pipex, int i, char *cmd)
{
	get_cmd(pipex, cmd, i);
	if (i == 0)
	{
		child1_process(pipex, i);
	}
	else if (i == pipex->ac - 4)
	{
		child_last_process(pipex, i);
	}
	else
	{
		dup2(pipex->fd[i - 1][0], 0);
		dup2(pipex->fd[i][1], 1);
		close_pipex(pipex);
	}
}

void	ft_lunch(t_data *pipex, int ac, char **env, t_malloc **ft)
{
	int	i;

	i = 0;
	while (i < ac - 3)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			perror("fork");
		if (pipex->pid[i] == 0)
		{
			process(pipex, i, pipex->av[i]);
			execute_cmd(pipex, env, ft, i);
		}
		else
			parent_process(pipex, &i);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data		pipex;
	t_malloc	*ft;
	int			i;

	if (ac < 5)
	{
		ft_putstr_fd("Error args\n", 2);
		exit(1);
	}
	i = 0;
	ft_init(&pipex, ac, av, env);
	ft_alloc_pipe(&pipex, &ft, ac);
	ft_pipe(&pipex, ac);
	ft_lunch(&pipex, ac, env, &ft);
	while (i < ac - 3)
	{
		waitpid(pipex.pid[i], &pipex.status, 0);
		if (pipex.status != -1)
			pipex.last_status = pipex.status >> 8;
		i++;
	}
	close_pipex(&pipex);
	return ((pipex.last_status));
}
