/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:15:28 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 09:10:13 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_env(char *const *envp)
{
	char	*path_env;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (path_env);
}

static char	*get_cmd(char *command)
{
	char	*cmd;
	char	*space_pos;

	cmd = NULL;
	space_pos = ft_strchr(command, ' ');
	if (space_pos != NULL)
	{
		cmd = ft_calloc(1, (space_pos - command + 1));
		if (!cmd)
			error_exit("Malloc cmd error");
		ft_strlcpy(cmd, command, space_pos - command + 1);
	}
	else
	{
		cmd = ft_strdup(command);
		if (!cmd)
			error_exit("Strdup error");
	}
	return (cmd);
}

static char	*build_path(char **paths, char *command)
{
	char	*full_path;
	int		i;
	size_t	len;

	i = -1;
	while (paths[++i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(command) + 2;
		full_path = ft_calloc(1, len);
		if (!full_path)
			error_exit("Malloc error");
		ft_strlcpy(full_path, paths[i], len);
		ft_strlcat(full_path, "/", len);
		ft_strlcat(full_path, command, len);
		if (access(full_path, X_OK) == 0)
		{
			free(command);
			free_split(paths);
			return (full_path);
		}
		free(full_path);
	}
	free(command);
	free_split(paths);
	return (NULL);
}

char	*get_path(t_pipex *pipex, char *command)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	char	*cmd;

	path_env = get_env(pipex->envp);
	paths = ft_split(path_env, ':');
	if (!paths)
		error_exit("Split error");
	cmd = get_cmd(command);
	full_path = build_path(paths, cmd);
	return (full_path);
}
