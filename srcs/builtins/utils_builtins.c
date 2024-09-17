#include "../../includes/minishell.h"

static void	both_are_wrong(t_pipex *pipex, bool should_exit);

int	is_builtins(t_cmd *command)
{
	if (command->cmd)
	{
		if ((ft_strcmp(command->cmd, "cd") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "echo") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "pwd") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "export") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "unset") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "env") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "exit") == 0))
			return (ISBUILTINS);
	}
	return (ISNOTBUILTINS);
}

void	execute_builtins(t_pipex *pipex)
{
	open_files(pipex);
	if (files_are_valid(pipex, false) == FAILURE)
		return ;
	if (ft_strcmp(pipex->cmd->cmd, "echo") == 0)
		builtin_echo(pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "cd") == 0)
		builtin_cd(pipex->env, pipex->cmd->args, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "pwd") == 0)
		builtin_pwd(pipex->env, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "export") == 0)
		builtin_export(pipex->env, pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "unset") == 0)
		builtin_unset(pipex->env, pipex->cmd->args);
	else if (ft_strcmp(pipex->cmd->cmd, "env") == 0)
		builtin_env(pipex->env, pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "exit") == 0)
		builtin_exit(pipex->env, pipex->cmd);
}

int	files_are_valid(t_pipex *pipex, bool should_exit)
{
	if (pipex->infile_error || pipex->outfile_error)
	{
		both_are_wrong(pipex, should_exit);
		if (pipex->infile_error)
		{
			open(pipex->infile_error->element, O_RDONLY);
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ",
			pipex->infile_error->element);
			perror("");
			if (should_exit == true)
				exit(EXIT_FAILURE);
		}
		if (pipex->outfile == FAILURE)
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: Permission denied\n", \
			pipex->outfile_error);
			if (should_exit == true)
				exit(EXIT_FAILURE);
		}
		g_exit_code = EXIT_FAILURE;
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	both_are_wrong(t_pipex *pipex, bool should_exit)
{
	if (pipex->infile_error && pipex->outfile_error)
	{
		if (pipex->infile_error->index < pipex->outfile_error->index)
		{
			open(pipex->infile_error->element, O_RDONLY);
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ",
			pipex->infile_error->element);
			perror("");
			if (should_exit == true)
				exit(EXIT_FAILURE);
		}
		ft_fprintf(STDERR_FILENO, "Fraudistan: %s: Permission denied\n", \
		pipex->outfile_error->element);
		if (should_exit == true)
			exit(EXIT_FAILURE);
	}
}
