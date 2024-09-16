#include "../../includes/minishell.h"

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
	if (ft_strcmp(pipex->cmd->cmd, "echo") == 0)
		builtin_echo(pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "cd") == 0)
		builtin_cd(pipex->env, pipex->cmd->args, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "pwd") == 0)
		builtin_pwd(pipex->env, pipex->cmd->args, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "export") == 0)
		builtin_export(pipex->env, pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "unset") == 0)
		builtin_unset(pipex->env, pipex->cmd->args);
	else if (ft_strcmp(pipex->cmd->cmd, "env") == 0)
		builtin_env(pipex->env, pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "exit") == 0)
		builtin_exit(pipex->env, pipex->cmd);
	else
		printf("%s: command not found\n", pipex->cmd->cmd);
}

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*temp;

	copy = NULL;
	temp = env;
	while (temp)
	{
		add_node(&copy, temp->line);
		temp = temp->next;
	}
	return (copy);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->line);
		free(head->var);
		free(head->args);
		free(head);
		head = tmp;
	}
}

char	*get_env(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
			return (env->args);
		env = env->next;
	}
	return (NULL);
}
