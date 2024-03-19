#include "libft/libft.h"
#include "minishell.h"
#include <sys/_types/_sigset_t.h>
#include <sys/signal.h>

volatile sig_atomic_t g_sig;

void	parsing(t_parsedata *parse, t_execdata *exec)
{
	parse->token_head = NULL;
	parsing_env(parse, exec->env); //env parsing
	split_token(&(parse->token_head), parse->env_str); //make token linked list
	if (parse->token_head != NULL)
	{
		exec->pipe = NULL;
		beautify_token(&(parse->token_head), &(exec->pipe)); //split pipe
	}
	free(parse->str);
	free(parse->env_str);
}

void	handler(int signum, struct __siginfo *info, void *s)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() < 0)
			error_exit("readline error", 0, 0, EXIT_FAILURE);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		return ;
}

void	free_token(void *node)
{
	t_list	*nd;
	t_token	*token;

	nd = (t_list *)node;
	token = (t_token *)nd->content;
	free(token->str);
	free(token);
	free(node);
}

void	free_tokens_in_pipe(void *node)
{
	t_list	*pipe_tokens;

	pipe_tokens = (t_list *)node;
	if (pipe_tokens != NULL)
		ft_lstclear(&pipe_tokens, free_token);
}



int main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	t_parsedata	parse;
	struct sigaction	act;
	
	data.env = envp_to_lst(envp);
	// signal(SIGINT, &handler);
	// signal(SIGQUIT, &handler);
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	// sigaddset(&act.sa_mask, SIGSTOP);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handler;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (1);
	// if (sigaction(SIGSTOP, &act, NULL) == -1)
	// 	return (1);
	while (1)
	{
		parse.str = readline("~ ");
		if (parse.str == NULL)
			exit_after_print(EXIT_SUCCESS);
		if(*parse.str)
		{
			add_history(parse.str);
			parsing(&parse, &data);
			if (parse.token_head == NULL)
				printf("syntax error\n");
			else
				exec(&data);
		}
		// ft_lstclear(&data.pipe, free_tokens_in_pipe);
	}
	return (0);
}

// void check()
// {
// 	system("leaks --list a.out");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_execdata	data;
// 	t_list		*new;
// 	t_list		*first_token;
// 	char		*buff;
	
// 	atexit(check);
// 	data.env = envp_to_lst(envp);
// 	data.pipe = ft_malloc_err(sizeof(t_list));

// 	t_token *t1 = ft_malloc_err(sizeof(t_token));
// 	first_token = ft_lstnew(t1);
// 	data.pipe->content = first_token;
// 	data.pipe->next = NULL;
	
// 	t_token *t2 = ft_malloc_err(sizeof(t_token));
// 	new = ft_lstnew(t2);
// 	ft_lstadd_back(&first_token, new);
	
// 	t_token *t3 = ft_malloc_err(sizeof(t_token));
// 	new = ft_lstnew(t3);
// 	ft_lstadd_back(&first_token, new);
	
// 	t_token *t4 = ft_malloc_err(sizeof(t_token));
// 	new = ft_lstnew(t4);
// 	ft_lstadd_back(&first_token, new);
	
// 	t_token *t5 = ft_malloc_err(sizeof(t_token));
// 	new = ft_lstnew(t5);
// 	ft_lstadd_back(&first_token, new);

// 	t1->str = "a";
// 	t1->type=TYPE_INPUT;

// 	t2->str = "eof";
// 	t2->type=TYPE_HEREDOC;

// 	t1->str = "env";
// 	t1->type=TYPE_DEFAULT;

// 	t4->str = "-al";
// 	t4->type=TYPE_DEFAULT;
// 	t5->str = "out_a";
// 	t5->type=TYPE_OUTPUT_A;


// 	// t_list		*new_pipe;
// 	// t_list		*sec_first_token;
	

// 	// new_pipe = ft_malloc_err(sizeof(t_list));
// 	// t_token *t21 = ft_malloc_err(sizeof(t_token));
// 	// sec_first_token = ft_lstnew(t21);
// 	// new_pipe->content = sec_first_token;
// 	// new_pipe->next = NULL;
// 	// ft_lstadd_back(&data.pipe, new_pipe);

// 	// t_token *t22 = ft_malloc_err(sizeof(t_token));
// 	// new = ft_lstnew(t22);
// 	// ft_lstadd_back(&sec_first_token, new);
	
// 	// // t_token *t23 = ft_malloc_err(sizeof(t_token));
// 	// // new = ft_lstnew(t23);
// 	// // ft_lstadd_back(&sec_first_token, new);
	
// 	// t_token *t24 = ft_malloc_err(sizeof(t_token));
// 	// // printf("t24: %p\n", t24);
// 	// new = ft_lstnew(t24);
// 	// // printf("new: %p\n", new);
// 	// ft_lstadd_back(&sec_first_token, new);
	
// 	// t_token *t25 = ft_malloc_err(sizeof(t_token));
// 	// // printf("t25: %p\n", t25);
// 	// new = ft_lstnew(t25);
// 	// // printf("new: %p\n", new);
// 	// ft_lstadd_back(&sec_first_token, new);

// 	// t21->str = "grep";
// 	// t21->type=TYPE_DEFAULT;

// 	// t22->str = "minishell";
// 	// t22->type=TYPE_DEFAULT;

// 	// // t23->str = "grep";
// 	// // t23->type=TYPE_DEFAULT;
// 	// t24->str = "out_t";
// 	// t24->type=TYPE_OUTPUT_T;
// 	// t25->str = "out_a";
// 	// t25->type=TYPE_OUTPUT_A;

// 	while (1)
// 	{
// 		buff = readline("~ ");
// 		if (buff == NULL)
// 			exit(EXIT_SUCCESS);
// 		if(buff)
// 		{
// 			add_history(buff);
// 			exec(&data);
// 		}
// 		free(buff);
// 	}

// 	// while (data.env != NULL)
// 	// {
// 	// 	printf("%s\n", data.env->content);
// 	// 	data.env = data.env->next;
// 	// }

// 	exit(EXIT_SUCCESS);
// 	return (0);
// }