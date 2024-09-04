NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
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
		srcs/exec/pipex/exec.c\
		srcs/exec/pipex/free.c\
		srcs/exec/pipex/here_doc.c\
		srcs/exec/pipex/path_building.c\
		srcs/exec/pipex/pipex.c\
		srcs/exec/pipex/utils_pipex.c\
		srcs/exec/builtins/utils_builtins.c\
		srcs/exec/builtins/builtins_env.c\
		srcs/exec/builtins/builtins_other.c\
		srcs/exec/builtins/chain_list_utils.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIBFT) pimped $(OBJS)
	@sleep 0.8
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@$(RM) errors.tmp;

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES) 2>> errors.tmp || \
	{ \
		echo "\033[u\033[1A\033[2K│$(RED) Compilation of $(NAME) failed X$(NC)	       │"; \
		echo "└──────────────────────────────────────────────┘"; \
		sed "s/error:/\x1b[1;31m&\x1b[0m/g" errors.tmp; \
		$(RM) errors.tmp; \
		exit 1; \
	}

pimped:
	@echo "$(NC)┌─────$(NAME)────────────────────────────────┐"
	@echo "│$(BLUE) Compiling $(NAME) in progress... ⌛$(NC)	       │"
	@echo "\033[s└──────────────────────────────────────────────┘"


$(LIBFT):
	@make -s -C $(LIBFT_PATH)

all: $(NAME)


clean:
	@echo "$(NC)┌─────clean $(NAME)──────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) objects in progress... ⌛$(NC) │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(OBJS)
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

re: fclean all

norme:
	@echo "$(BLUE)Checking norminette in progress... ⌛"
	@if norminette srcs includes libft > norme.tmp;\
	then echo "$(GREEN)Norminette check passed successfully ✓";\
	else echo "$(RED)Norminette check failed.$(NC)";\
	cat norme.tmp | grep "Error";\
	fi
	@$(RM) norme.tmp

.PHONY: all clean fclean re
