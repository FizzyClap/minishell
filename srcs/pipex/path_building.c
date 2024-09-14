/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:25:55 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 09:45:34 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path_in_env(t_env *env)
{
	t_env	*current;
	char	*path_env;

	path_env = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->var, "PATH") == 0)
		{
			path_env = ft_strdup(current->args);
			break ;
		}
		current = current->next;
	}
	return (path_env);
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
			ft_free_tab(paths);
			return (full_path);
		}
		free(full_path);
	}
	free(command);
	ft_free_tab(paths);
	return (NULL);
}

char	*get_path(t_pipex *pipex)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	char	*cmd;

	path_env = get_path_in_env(pipex->env);
	paths = ft_split(path_env, ':');
	cmd = NULL;
	if (!paths)
	{
		free(path_env);
		free_pipex(pipex);
		error_exit("Split error");
	}
	if (pipex->cmd->cmd)
		cmd = ft_strdup(pipex->cmd->cmd);
			if (!cmd)
				return (NULL);
	full_path = build_path(paths, cmd);
	if (!full_path)
		return (NULL);
	free(path_env);
	return (full_path);
}
