NAME = my_terminal

CC = cc

LIBFT = libft/libft.a

SRC_DIR = src
OBJ_DIR = obj

INCLUDES = -Iheaders -Ilibft

BASE_SRC = 	main.c							\
			t_point.c						\
			list.c						\
			writing_utils/init_chars.c		\
			writing_utils/write_it.c		\
			shell/handle_input.c			\
			shell/init_shell.c				\
			shell/brackets.c				\
			shell/help.c					\
			shell/exec.c					\
			shell/free.c					\
			shell/builtins.c			

SRC = $(addprefix $(SRC_DIR)/, $(BASE_SRC))

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DEP = $(OBJ:.o=.d)

MLX = minilibx-linux

all : $(MLX) $(NAME)

$(MLX) :
	@echo "\n\033[0;32mCloning MLX..\e[m"
	@git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux > /dev/null 2>&1
	@echo "\033[0;32mCompilating MLX..\e[m"
	@make -C minilibx-linux > /dev/null 2>&1

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MMD -MP $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@echo "\n\033[0;32mCreating obj directory..\e[m"
	@mkdir -p $(OBJ_DIR)/writing_utils $(OBJ_DIR)/shell


CFLAGS = -Wall -Wextra -Werror -g3

MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

$(NAME) : $(OBJ)
	@echo "\033[0;32mCompilating libft..\e[m"
	@make -s -C libft
	@echo "\033[0;32mCompilating My_term..\e[m"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(INCLUDES) -o $(NAME) -lm -lreadline
	@echo "\033[1;32mMy_term successfully compilated !\n\e[m"

clean :
	@echo "\n\033[0;31mDeleting libft objects..\e[m"
	@make -s clean -C libft
	@echo "\033[0;31mDeleting My_term objects..\e[m"
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;31mSuccessfully deleted objects !\n\e[m"

fclean : clean
	@echo "\n\033[0;31mDeleting libft executable..\e[m"
	@make -s fclean -C libft
	@echo "\n\033[0;31mDeleting MLX..\e[m"
	@rm -rf $(MLX)
	@echo "\033[0;31mDeleting executable..\e[m"
	@rm -f $(NAME)
	@echo "\033[1;31mSuccessfully deleted executables !\n\e[m"

re : fclean all

-include $(DEP)

.PHONY : all clean fclean re 

.SILENT : $(OBJ)
