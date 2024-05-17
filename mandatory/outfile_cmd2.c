/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:00:19 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/16 20:33:14 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd2(t_data *pipex, char **av, t_malloc **ft)
{
	char	**command;
	int		i;

	i = 0;
	if (ft_strlen(av[3]) == 0)
		exit(0);
	command = ft_split_str(av[3], " \n\t\f\r");
	if (!command[0])
		return ;
	while (command[i])
		i++;
	pipex->cmd2 = ft_malloc(ft, sizeof(char *) * (i + 1));
	if (!pipex->cmd2)
		return ;
	i = 0;
	while (command[i])
	{
		pipex->cmd2[i] = command[i];
		i++;
	}
	pipex->cmd2[i] = NULL;
	free(command);
}

int	check_env2(t_data *pipex, t_malloc **ft)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->env[i])
	{
		path = ft_strjoin(pipex->env[i], "/", ft);
		path = ft_strjoin(path, pipex->cmd2[0], ft);
		if (access(path, X_OK) != -1)
		{
			pipex->cmd2_loc = path;
			return (1);
		}
		path = ft_strjoin("./", pipex->cmd2[0], ft);
		if (access(path, X_OK) != -1 && pipex->valid == 1)
		{
			pipex->cmd2_loc = pipex->cmd2[0];
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	get_cmd2_loc(t_data *pipex, t_malloc **ft)
{
	char	*cmd;

	if (pipex->cmd2[0] == NULL)
		exit(0);
	cmd = ft_strrchr(pipex->cmd2[0], '/');
	if (pipex->cmd2[0][0] == '.' && pipex->cmd2[0][1] == '\0')
	{
		write(2,
			".: filename argument required\n.: usage: . filename [arguments]\n",
			64);
		exit(2);
	}
	if (cmd != NULL)
	{
		if (access(pipex->cmd2[0], X_OK) != -1)
		{
			pipex->cmd2_loc = pipex->cmd2[0];
			return (1);
		}
		else
			return (2);
	}
	cmd = pipex->cmd2[0];
	return (check_env2(pipex, ft));
}

void	outfile_cmd_process(t_data *pipex, t_malloc **ft)
{
	int	valid;

	valid = get_cmd2_loc(pipex, ft);
	if (!valid)
		command_not_found(pipex->cmd2[0]);
	else if (valid == 2)
		command_error(pipex->cmd2[0]);
}
