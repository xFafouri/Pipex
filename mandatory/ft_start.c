/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:19:40 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/14 12:53:53 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check(t_data *pipex, int ac, char **av, char **env)
{
	if (ac != 5)
	{
		write(2, "Error args\n", 12);
		exit(1);
	}
	pipex->valid = 0;
	ft_path(pipex, env);
	pipe(pipex->pipefd);
	if (pipe(pipex->pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pipex->infile = av[1];
	pipex->outfile = av[4];
}

void	ft_init(t_data *pipex, int ac, char **av, char **env)
{
	pipex->status = 0;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->cmd1_loc = NULL;
	pipex->cmd2_loc = NULL;
	ft_check(pipex, ac, av, env);
}
