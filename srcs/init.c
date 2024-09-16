#include "../includes/minishell.h"

void	init_env(t_env **env, char *const *envp)
{
	int	i;

	if (!envp[0])
	{
		ft_putstr_fd("Fraudistan: environment is missing\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (envp[++i])
		add_node(env, envp[i]);
}

void	init_pipex(t_pipex *pipex, t_cmd *command, t_env *env)
{
	t_cmd	*size;
	int		i;

	pipex->env = env;
	pipex->cmd = command;
	pipex->i = -1;
	pipex->print_msg = false;
	pipex->infile_exist = true;
	pipex->limiter = NULL;
	size = pipex->cmd;
	pipex->nb_pipes = list_cmd_size(size) - 1;
	i = -1;
	pipex->exit_status = 0;
	pipex->status = 1;
	pipex->pipefd = malloc(sizeof(int *) * pipex->nb_pipes);
	if (!pipex->pipefd)
		return ;
	i = -1;
	while (++i < pipex->nb_pipes)
		pipex->pipefd[i] = ft_calloc(sizeof(int), 2);
	pipex->child = ft_calloc(sizeof(pid_t), (pipex->nb_pipes + 1));
	if (!pipex->child)
		return ;
}
