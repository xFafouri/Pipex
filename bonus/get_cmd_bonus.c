/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:15:14 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/18 13:05:52 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_empty(t_data *pipex, char *cmd, int i)
{
	if (ft_strlen(cmd) == 0 && i == 0)
		exit(0);
	if (ft_strlen(cmd) == 0 && i == pipex->ac - 2)
		exit(0);
	if (!ft_strlen(cmd))
		exit(1);
}

void	get_cmd(t_data *pipex, char *cmd, int i)
{
	char	**command;
	int		j;

	check_empty(pipex, cmd, i);
	command = ft_split_str(cmd, " \t\r\f\n");
	if (command[0] == NULL)
		return ;
	j = 0;
	while (command[j] != NULL)
		j++;
	pipex->cmd = malloc(sizeof(char **) * (j + 1));
	if (pipex->cmd == NULL)
		return ;
	j = 0;
	while (command[j] != NULL)
	{
		pipex->cmd[j] = command[j];
		j++;
	}
	pipex->cmd[j] = NULL;
	free(command);
}

int	check_env(t_data *pipex, t_malloc **ft)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->env[i])
	{
		path = ft_strjoin(pipex->env[i], "/", ft);
		path = ft_strjoin(path, pipex->cmd[0], ft);
		if (access(path, X_OK) != -1)
		{
			pipex->cmd_loc = path;
			return (1);
		}
		path = ft_strjoin("./", pipex->cmd[0], ft);
		if (access(path, X_OK) != -1 && pipex->valid == 1)
		{
			pipex->cmd_loc = pipex->cmd[0];
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	get_cmd_loc(t_data *pipex, t_malloc **ft)
{
	char	*cmd;

	if (pipex->cmd[0] == NULL)
		exit(0);
	if (pipex->cmd[0][0] == '.' && pipex->cmd[0][1] == '\0')
	{
		write(2,
			".: filename argument required\n.: usage: . filename [arguments]\n",
			64);
		exit(2);
	}
	cmd = ft_strchr(pipex->cmd[0], '/');
	if (cmd != NULL)
	{
		if (access(pipex->cmd[0], R_OK) != -1)
		{
			pipex->cmd_loc = pipex->cmd[0];
			return (1);
		}
		else
			return (2);
	}
	cmd = pipex->cmd[0];
	return (check_env(pipex, ft));
}

void	execute_cmd(t_data *pipex, char **env, t_malloc **ft, int i)
{
	int	valid;

	valid = 0;
	valid = get_cmd_loc(pipex, ft);
	if (!valid)
		command_not_found(pipex->cmd[0]);
	else if (valid == 2)
		command_error(pipex->cmd[0]);
	execve(pipex->cmd_loc, pipex->cmd, env);
	if (open(pipex->av[i], O_DIRECTORY) != -1)
	{
		ft_putstr_fd(pipex->av[i], 2);
		write(2, ": is a directory\n", 18);
		exit(126);
	}
	else
		(perror(""), exit(126));
}
