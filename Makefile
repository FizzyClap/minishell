NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
LIBFT = libft/libft.a
LIBFT_PATH = ./libft
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
LDFLAGS = $(LIBFT_FLAGS) -lreadline -lhistory -lncurses
INCLUDES = -I./includes -I$(LIBFT_PATH)/includes
RM = rm -rf
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m

SRCS =	srcs/main.c\
		srcs/builtins/builtins_cd.c\
		srcs/builtins/utils_builtins.c\
		srcs/builtins/builtins_env.c\
		srcs/builtins/builtins_other.c\
		srcs/builtins/chain_list_utils.c\
		srcs/builtins/utils_env.c\
		srcs/lexer/lexer_lst.c\
		srcs/lexer/lexer_redir.c\
		srcs/lexer/lexer_utils.c\
		srcs/lexer/lexer.c\
		srcs/lexer/prompt_loop.c\
		srcs/parser/free_utils.c\
		srcs/parser/parser.c\
		srcs/parser/parser_lst.c\
		srcs/parser/split_cmd.c\
		srcs/pipex/execution.c\
		srcs/pipex/here_doc.c\
		srcs/pipex/init.c\
		srcs/pipex/open_files.c\
		srcs/pipex/path_building.c\
		srcs/pipex/tab_env.c\
		srcs/pipex/utils_files.c\
		srcs/pipex/utils_pipex.c\
		srcs/debug/print.c\
		srcs/signals/signals.c\
		srcs/var_env/parsing_env.c\
		srcs/var_env/parsing_env_utils.c\
		srcs/var_env/var_env_lst.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@$(RM) errors.tmp

.c.o:
	@if [ ! -f .mandatory ]; then \
		echo "$(NC)┌─────$(NAME)────────────────────────────────┐"; \
		echo "│$(BLUE) Compiling $(NAME) in progress... ⌛$(NC)	       │"; \
		echo "\033[s└──────────────────────────────────────────────┘"; \
		touch .mandatory; \
	fi
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES) 2>> errors.tmp || \
	{ \
		echo "\033[u\033[1A\033[2K│$(RED) Compilation of $(NAME) failed X$(NC)	       │"; \
		echo "└──────────────────────────────────────────────┘"; \
		sed "s/error:/\x1b[1;31m&\x1b[0m/g" errors.tmp; \
		$(RM) errors.tmp; \
		exit 1; \
	}

all: $(NAME)
	@$(RM) .mandatory

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

clean:
	@echo "$(NC)┌─────clean $(NAME)──────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) objects in progress... ⌛$(NC) │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(OBJS) .mandatory
	@echo "│$(GREEN) Cleaning of $(NAME) objects completed ✓ $(NC)   │"
	@echo "└──────────────────────────────────────────────┘"

fclean: clean
	@echo "$(NC)┌─────fclean $(NAME)─────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) in progress... ⌛$(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(NAME)
	@echo "│$(GREEN) Cleaning of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@make -s -C $(LIBFT_PATH) fclean

re: fclean all

norme:
	@echo "$(BLUE)Checking norminette in progress... ⌛"
	@if norminette srcs includes libft > norme.tmp;\
	then echo "$(GREEN)Norminette check passed successfully ✓";\
	else echo "$(RED)Norminette check failed.$(NC)";\
	cat norme.tmp | grep "Error";\
	fi
	@$(RM) norme.tmp

.PHONY: all clean fclean re norme
