#include "../../include/minishell.h"

static void	cleanup_heredoc_file(void)
{
	unlink(".heredoc_tmp");
}

int	handle_heredoc(t_command *cmd)
{
	char	*line;
	int		heredoc_fd;

	if (!cmd->heredoc_delim)
		return (0);
	heredoc_fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
	{
		perror("minishell: heredoc");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			ft_gc_free(line);
			break ;
		}
		if (write(heredoc_fd, line, ft_strlen(line)) == -1 || write(heredoc_fd,
				"\n", 1) == -1)
		{
			perror("minishell: heredoc write");
			ft_gc_free(line);
			close(heredoc_fd);
			return (-1);
		}
		ft_gc_free(line);
	}
	close(heredoc_fd);
	if (cmd->input_file)
		ft_gc_free(cmd->input_file);
	cmd->input_file = ft_strdup(".heredoc_tmp");
	if (!cmd->input_file)
	{
		perror("minishell: memory allocation failed");
		return (-1);
	}
	return (0);
}

int	handle_input_redirection(t_command *cmd)
{
	if (!cmd->input_file)
		return (0);
	if (cmd->input_fd != STDIN)
		close(cmd->input_fd);
	cmd->input_fd = open(cmd->input_file, O_RDONLY);
	if (cmd->input_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd->input_file, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (-1);
	}
	if (cmd->input_file && ft_strcmp(cmd->input_file, ".heredoc_tmp") == 0)
		cleanup_heredoc_file();
	return (0);
}

int	handle_output_redirection(t_command *cmd)
{
	int	flags;

	if (!cmd->output_file)
		return (0);
	if (cmd->output_fd != STDOUT)
		close(cmd->output_fd);
	flags = O_WRONLY | O_CREAT;
	flags |= cmd->append_mode ? O_APPEND : O_TRUNC;
	cmd->output_fd = open(cmd->output_file, flags, 0644);
	if (cmd->output_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd->output_file, STDERR);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", STDERR);
		else
			ft_putstr_fd(": Error opening file\n", STDERR);
		return (-1);
	}
	return (0);
}

void	cleanup_redirections(t_command *cmd)
{
	if (cmd->input_file)
	{
		ft_gc_free(cmd->input_file);
		cmd->input_file = NULL;
	}
	if (cmd->output_file)
	{
		ft_gc_free(cmd->output_file);
		cmd->output_file = NULL;
	}
	if (cmd->heredoc_delim)
	{
		ft_gc_free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
	}
	if (cmd->input_fd != STDIN)
	{
		close(cmd->input_fd);
		cmd->input_fd = STDIN;
	}
	if (cmd->output_fd != STDOUT)
	{
		close(cmd->output_fd);
		cmd->output_fd = STDOUT;
	}
}