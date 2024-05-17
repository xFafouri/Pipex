/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:41:24 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/16 09:42:28 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command_not_found(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" :command not found ", 2);
	write(2, "\n", 1);
	exit(127);
}

void	command_error(char *s)
{
	perror(s);
	exit(127);
}

void	error_pid(int pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
}

void	error_fd1(int fd, t_data *pipex)
{
	if (fd == -1)
	{
		if (open(pipex->infile, O_RDONLY) == -1)
		{
			if (access(pipex->infile, F_OK) == 0)
			{
				perror(pipex->infile);
				exit(1);
			}
			else
			{
				ft_putstr_fd(pipex->infile, 2);
				write(2, " : No such file or directory\n", 30);
				exit(1);
			}
		}
	}
}

void	error_fd2(int fd, t_data *pipex)
{
	if (fd == -1)
	{
		perror(pipex->infile);
		exit(1);
	}
}
