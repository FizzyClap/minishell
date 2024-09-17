/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:01 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:16:55 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_exist_in_path(t_pipex *pipex);
static char	*get_path(t_pipex *pipex);
static char	*extract_path_in_env(t_env *env);
static char	*build_path(char **paths, char *command);

void	exec_command(t_pipex *pipex)
{
	char	*path;

	if (is_builtins(pipex->cmd))
	{
		execute_builtins(pipex);
		exit(EXIT_SUCCESS);
	}
	create_tab_env(pipex->env);
	cmd_exist_in_path(pipex);
	path = get_path(pipex);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", pipex->cmd->cmd);
		free_pipex(pipex);
		exit(COMMAND_NOT_FOUND);
	}
	free(pipex->cmd->args[0]);
	pipex->cmd->args[0] = path;
	if (execve(pipex->cmd->args[0], pipex->cmd->args, pipex->env->tab_env) \
		== FAILURE)
	{
		free_pipex(pipex);
		error_exit("Error executing command");
	}
}

static void	cmd_exist_in_path(t_pipex *pipex)
{
	if (pipex->cmd->cmd && access(pipex->cmd->args[0], X_OK) == 0)
	{
		if (execve(pipex->cmd->args[0], pipex->cmd->args, pipex->env->tab_env) \
			== FAILURE)
		{
			if (ft_strncmp(pipex->cmd->args[0], "./", 2) == 0 || \
				ft_strncmp(pipex->cmd->args[0], "/", 1) == 0)
			{
				ft_fprintf(STDERR_FILENO, "Fraudistan: %s: Is a directory\n", \
				pipex->cmd->args[0]);
				g_exit_code = EXIT_PERMISSION_DENIED;
			}
			else
			{
				ft_fprintf(STDERR_FILENO, "Fraudistan: %s: command not found\n",
					pipex->cmd->args[0]);
				g_exit_code = COMMAND_NOT_FOUND;
			}
			free_pipex(pipex);
			exit(g_exit_code);
		}
	}
	verif_is_executable(pipex);
}

static char	*get_path(t_pipex *pipex)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	char	*cmd;

	path_env = extract_path_in_env(pipex->env);
	paths = ft_split(path_env, ':');
	free(path_env);
	cmd = NULL;
	if (!paths)
	{
		free_pipex(pipex);
		error_exit("Split error");
	}
	if (pipex->cmd->cmd)
	{
		cmd = ft_strdup(pipex->cmd->cmd);
		if (!cmd)
			return (NULL);
	}
	full_path = build_path(paths, cmd);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static char	*extract_path_in_env(t_env *env)
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
			if (!path_env)
				return (NULL);
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
	while (command && paths[++i])
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
