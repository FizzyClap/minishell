#include "../../includes/minishell.h"

static void	execute_child(t_pipex *pipex, int i);
static void	inter_cmd(t_pipex *pipex, int i);
static void	dup_and_exec(t_pipex *pipex, int inputfd, int outputfd);

void	execute_pipeline(t_cmd *command, t_env *env)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	init_pipex(pipex, command, env);
	execute_pipes(pipex);
	i = -1;
	while (++i <= pipex->nb_pipes)
	{
		waitpid(pipex->child[i], &pipex->status, 0);
		if (WIFEXITED(pipex->status))
			g_exit_code = WEXITSTATUS(pipex->status);
		else if (WIFSIGNALED(pipex->status))
			g_exit_code = WTERMSIG(pipex->status) + 128;
	}
	free_pipex(pipex);
}

void	execute_pipes(t_pipex *pipex)
{
	while (++pipex->i <= pipex->nb_pipes)
	{
		if (pipex->cmd && pipex->cmd->next)
			if (pipe(pipex->pipefd[pipex->i]) == FAILURE)
				error_exit("Pipe error");
		if (pipex->nb_pipes == 0 && is_builtins(pipex->cmd))
		{
			execute_builtins(pipex);
			return ;
		}
		pipex->child[pipex->i] = fork_child();
		if (pipex->child[pipex->i] == 0)
			execute_child(pipex, pipex->i);
		else
		{
			if (pipex->i > 0)
				close(pipex->pipefd[pipex->i - 1][0]);
			if (pipex->i < pipex->nb_pipes)
				close(pipex->pipefd[pipex->i][1]);
		}
		if (pipex->cmd && pipex->cmd->next)
			pipex->cmd = pipex->cmd->next;
	}
}

static void	execute_child(t_pipex *pipex, int i)
{
	open_files(pipex);
	if (i == 0)
	{
		if (pipex->nb_pipes > 0)
			close(pipex->pipefd[i][0]);
		if (i == pipex->nb_pipes || pipex->outfile != STDOUT_FILENO)
			dup_and_exec(pipex, pipex->infile, pipex->outfile);
		else
			dup_and_exec(pipex, pipex->infile, pipex->pipefd[i][1]);
	}
	else if (i == pipex->nb_pipes)
	{
		if (pipex->infile != STDIN_FILENO)
			dup_and_exec(pipex, pipex->infile, pipex->outfile);
		else
			dup_and_exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile);
	}
	else
		inter_cmd(pipex, i);
}

static void	inter_cmd(t_pipex *pipex, int i)
{
	close(pipex->pipefd[i][0]);
	if (pipex->infile != STDIN_FILENO && pipex->outfile != STDOUT_FILENO)
		dup_and_exec(pipex, pipex->infile, pipex->outfile);
	else if (pipex->infile != STDIN_FILENO)
		dup_and_exec(pipex, pipex->infile, pipex->pipefd[i][1]);
	else if (pipex->outfile != STDOUT_FILENO)
		dup_and_exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile);
	else
		dup_and_exec(pipex, pipex->pipefd[i - 1][0], pipex->pipefd[i][1]);
}

static void	dup_and_exec(t_pipex *pipex, int inputfd, int outputfd)
{
	if (pipex->infile_exist == false || outputfd == FAILURE)
	{
		if (!pipex->infile_exist && open(pipex->infile_error, O_RDONLY) < 0)
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ", pipex->infile_error);
			perror("");
		}
		if (outputfd == FAILURE)
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: Permission denied\n", \
			pipex->outfile_error);
		g_exit_code = EXIT_FAILURE;
		exit(g_exit_code);
	}
	if (dup2(inputfd, STDIN_FILENO) == FAILURE)
		error_exit("Dup2 input error");
	if (dup2(outputfd, STDOUT_FILENO) == FAILURE)
		error_exit("Dup2 output error");
	if (inputfd != STDIN_FILENO)
		close(inputfd);
	if (outputfd != STDOUT_FILENO)
		close(outputfd);
	exec_command(pipex);
	error_exit("Execve error");
}
