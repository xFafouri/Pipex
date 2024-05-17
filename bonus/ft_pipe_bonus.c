/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:07:45 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 17:17:00 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipex(t_data *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->ac - 4)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
}

void	ft_pipe(t_data *pipex, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 4)
	{
		if (pipe(pipex->fd[i]))
		{
			perror("");
			exit(1);
		}
		i++;
	}
}

void	ft_alloc_pipe(t_data *pipex, t_malloc **ft, int ac)
{
	int	i;

	i = 0;
	pipex->pid = ft_malloc(ft, sizeof(int) * (ac - 3));
	pipex->fd = ft_malloc(ft, ((ac - 3)) * (sizeof(int *)));
	while (i < ac - 3)
	{
		pipex->fd[i] = ft_malloc(ft, (2 * (sizeof(int))));
		i++;
	}
}
