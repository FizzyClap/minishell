NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m

SRCS =	srcs/ft_atoi.c\
		srcs/ft_bzero.c\
		srcs/ft_calloc.c\
		srcs/ft_change_bool.c\
		srcs/ft_count_args.c\
		srcs/ft_chrinstr.c\
		srcs/ft_isalnum.c\
		srcs/ft_isalpha.c\
		srcs/ft_isascii.c\
		srcs/ft_isdigit.c\
		srcs/ft_isprint.c\
		srcs/ft_itoa.c\
		srcs/ft_memchr.c\
		srcs/ft_memcmp.c\
		srcs/ft_memcpy.c\
		srcs/ft_memmove.c\
		srcs/ft_memset.c\
		srcs/ft_strchr.c\
		srcs/ft_strdup.c\
		srcs/ft_strlcat.c\
		srcs/ft_strlcpy.c\
		srcs/ft_strlen.c\
		srcs/ft_strcmp.c\
		srcs/ft_strncmp.c\
		srcs/ft_strnstr.c\
		srcs/ft_strrchr.c\
		srcs/ft_tolower.c\
		srcs/ft_toupper.c\
		srcs/ft_putchar_fd.c\
		srcs/ft_putstr_fd.c\
		srcs/ft_putnbr_fd.c\
		srcs/ft_putendl_fd.c\
		srcs/ft_split.c\
		srcs/ft_substr.c\
		srcs/ft_strmapi.c\
		srcs/ft_striteri.c\
		srcs/ft_strisnum.c\
		srcs/ft_strtrim.c\
		srcs/ft_strjoin.c\
		srcs/ft_lstadd_back.c\
		srcs/ft_lstadd_front.c\
		srcs/ft_lstclear.c\
		srcs/ft_lstdelone.c\
		srcs/ft_lstiter.c\
		srcs/ft_lstlast.c\
		srcs/ft_lstmap.c\
		srcs/ft_lstnew.c\
		srcs/ft_lstsize.c\
		srcs/ft_free_tab.c\
		printf/ft_printf_utils.c\
		printf/ft_printf.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\

OBJS = $(SRCS:.c=.o)

$(NAME): pimped $(OBJS)
	@sleep 0.8
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@$(RM) errors.tmp;

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES) 2>> errors.tmp || \
	{ \
		echo "\033[u\033[2K│$(RED) Compilation of $(NAME) failed X$(NC)	       │"; \
		echo "└──────────────────────────────────────────────┘"; \
		cat errors.tmp; \
		$(RM) errors.tmp; \
		exit 1; \
	}


all: $(NAME)

pimped:
	@echo "$(NC)┌─────libft────────────────────────────────────┐"
	@echo "│$(BLUE) Compilating $(NAME) in progress... ⌛$(NC)	       │"
	@echo "\033[s└──────────────────────────────────────────────┘"

clean:
	@echo "$(NC)┌─────clean $(NAME)────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) objects in progress... ⌛$(NC)   │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@$(RM) $(OBJS)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Cleaning of $(NAME) objects completed ✓ $(NC)     │"
	@echo "└──────────────────────────────────────────────┘"

fclean: clean
	@echo "$(NC)┌─────fclean $(NAME)───────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) in progress... ⌛$(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@$(RM) $(NAME)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Cleaning of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"

re: fclean all
