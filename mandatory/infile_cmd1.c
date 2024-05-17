/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_cmd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:37:38 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/17 17:52:53 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	check_env(t_data *pipex, t_malloc **ft)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->env[i])
	{
		path = ft_strjoin(pipex->env[i], "/", ft);
		path = ft_strjoin(path, pipex->cmd1[0], ft);
		if (access(path, X_OK) != -1)
		{
			pipex->cmd1_loc = path;
			return (1);
		}
		path = ft_strjoin("./", pipex->cmd1[0], ft);
		if (access(path, X_OK) != -1 && pipex->valid == 1)
		{
			pipex->cmd1_loc = pipex->cmd1[0];
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

void	get_cmd1(t_data *pipex, char **av, t_malloc **ft)
{
	char	**command;
	int		i;

	if (ft_strlen(av[2]) == 0)
		exit(0);
	i = 0;
	command = ft_split_str(av[2], " \t\r\f\n");
	if (!command[0])
		return ;
	while (command[i])
		i++;
	pipex->cmd1 = ft_malloc(ft, sizeof(char *) * (i + 1));
	if (!pipex->cmd1)
		return ;
	i = 0;
	while (command[i])
	{
		pipex->cmd1[i] = command[i];
		i++;
	}
	pipex->cmd1[i] = NULL;
	free(command);
}

int	get_cmd1_loc(t_data *pipex, t_malloc **ft)
{
	char	*cmd;

	if (pipex->cmd1[0] == NULL)
		exit(0);
	if (pipex->cmd1[0][0] == '.' && pipex->cmd1[0][1] == '\0')
	{
		write(2,
			".: filename argument required\n.: usage: . filename [arguments]\n",
			64);
		exit(2);
	}
	cmd = ft_strrchr(pipex->cmd1[0], '/');
	if (cmd != NULL)
	{
		if (access(pipex->cmd1[0], X_OK) != -1)
		{
			pipex->cmd1_loc = pipex->cmd1[0];
			return (1);
		}
		else
			return (2);
	}
	cmd = pipex->cmd1[0];
	return (check_env(pipex, ft));
}

void	infile_cmd_process(t_data *pipex, char **av, t_malloc **ft)
{
	int	valid;

	valid = 0;
	get_cmd1(pipex, av, ft);
	valid = get_cmd1_loc(pipex, ft);
	if (!valid)
		command_not_found(pipex->cmd1[0]);
	else if (valid == 2)
		command_error(pipex->cmd1[0]);
}
