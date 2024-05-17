/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:19:29 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 15:17:48 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child1_process(t_data *pipex, int i)
{
	int	infile;

	infile = open(pipex->infile, O_RDONLY);
	error_fd1(infile, pipex);
	dup2(infile, 0);
	dup2(pipex->fd[i][1], 1);
	close(infile);
	close_pipex(pipex);
}

void	child_last_process(t_data *pipex, int i)
{
	int	outfile;

	outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	error_fd2(outfile, pipex);
	dup2(pipex->fd[i - 1][0], 0);
	dup2(outfile, 1);
	close(outfile);
	close_pipex(pipex);
}

void	parent_process(t_data *pipex, int *i)
{
	if (*i > 0)
	{
		close(pipex->fd[*i - 1][0]);
		close(pipex->fd[*i - 1][1]);
	}
	(*i)++;
}
