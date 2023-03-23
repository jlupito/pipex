NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I./includes

#source
SRCS_DIR = sources/
SRCS = \

SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#objsm
OBJS = $(SRCS_PREFIXED:.c=.o)

all : $(NAME)

%.o: %.c ./includes/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lm -o $(NAME)
	@echo $(NAME) is built

clean :
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJS)
	@echo cleaning

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@echo "full clean"

re : fclean all

.PHONY	: all clean fclean re help