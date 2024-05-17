/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:50:22 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 16:20:07 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(t_data *pipex, char **env, char **av, t_malloc **ft)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	error_fd1(infile, av);
	infile_cmd_process(pipex, av, ft);
	dup2(infile, 0);
	close(infile);
	dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	execve(pipex->cmd1_loc, pipex->cmd1, env);
	if (open(av[2], O_DIRECTORY) != -1)
	{
		ft_putstr_fd(av[2], 2);
		write(2, ": is a directory\n", 18);
		exit(126);
	}
	else
	{
		(perror(""), exit(126));
	}
}

void	child2_process(t_data *pipex, char **env, char **av, t_malloc **ft)
{
	int	outfile;

	get_cmd2(pipex, av, ft);
	close(pipex->pipefd[1]);
	dup2(pipex->pipefd[0], 0);
	close(pipex->pipefd[0]);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	error_fd2(outfile, av);
	outfile_cmd_process(pipex, ft);
	dup2(outfile, 1);
	close(outfile);
	execve(pipex->cmd2_loc, pipex->cmd2, env);
	if (open(av[3], O_DIRECTORY) != -1)
	{
		ft_putstr_fd(av[3], 2);
		write(2, ": is a directory\n", 18);
		exit(126);
	}
	else
		(perror(""), exit(126));
}

void	parent_process(t_data *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->pid1, &pipex->status, 0);
	waitpid(pipex->pid2, &pipex->status, 0);
	ft_free2(pipex->env);
	free(pipex->cmd2_loc);
	if (pipex->cmd2)
		ft_free2(pipex->cmd2);
	if (pipex->cmd2_loc)
		free(pipex->cmd2_loc);
}

int	main(int ac, char **av, char **env)
{
	t_data		pipex;
	t_malloc	*ft;

	ft_init(&pipex, ac, av, env);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		error_pid(pipex.pid1);
	if (pipex.pid1 == 0)
		child1_process(&pipex, env, av, &ft);
	else
	{
		pipex.pid2 = fork();
		if (pipex.pid2 == -1)
			error_pid(pipex.pid1);
		if (pipex.pid2 == 0)
			child2_process(&pipex, env, av, &ft);
		else
			parent_process(&pipex);
	}
	return ((pipex.status >> 8));
}
