# -c: Tells the compiler to compile the source file into an object
#	file (.o) rather than an executable.
# $<: The first prerequisite, which here is the .c file from src/.
# -o $@: Specifies the output file name. $@ is a special variable
#	that represents the target, which in this rule is the .o file in $(OBJ_DIR).
# | is 'order-only prerequisites. You use when the dependance has
#	need to exist before to be executed.

###VARIABLES###

# name of the executable
NAME = minishell

# compilator and compilation flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lreadline -lncurses

# directories
IO_DIR = input_output/
MAIN_DIR = main/
ENV_DIR = environment/
EXEC_DIR = execution/
EXEC_BUILT_IN_DIR = execution/exec_built/
PARS_DIR = parsing/
ERR_DIR = error_and_free/
SIG_DIR = signal/
SRC_DIR = ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./include/
LIBFT_DIR = ./libft/
FT_PRINTF_DIR = ./ft_printf/

# custom libraries
LIBFT = $(LIBFT_DIR)libft.a
FT_PRINTF = $(FT_PRINTF_DIR)printf.a

# files
IO_FILES = in_out_manage.c in_out_utils.c
MAIN_FILES = main.c utils1.c utils2.c wait_and_status.c
ENV_FILES = environment.c env_utils.c env_print_utils.c env_generate.c env_built.c empty_env.c create_env.c
EXEC_FILES = execution.c exec_built_in.c exec_cmd.c exec_heredoc.c
EXEC_BUILT_FILES = exec_built_in_exit.c exec_built_in_cd.c exec_built_in_pwd.c \
		exec_built_in_unset.c exec_built_in_export.c exec_built_in_echo.c
PARS_FILES = parsing.c command_block.c command_block_utils.c \
		command_block_cmd.c parsing_token.c lexing_utils.c lexing.c lexing_token.c lexing_type.c check_esc_char.c lexing_miniutils.c
ERR_FILES = error_handle.c free_data.c free_data_utils.c
SIG_FILES = signal_init.c
FILES = $(addprefix $(EXEC_DIR), $(EXEC_FILES)) \
		$(addprefix $(PARS_DIR), $(PARS_FILES)) \
		$(addprefix $(EXEC_BUILT_IN_DIR), $(EXEC_BUILT_FILES)) \
		$(addprefix $(ERR_DIR), $(ERR_FILES)) \
		$(addprefix $(SIG_DIR), $(SIG_FILES)) \
		$(addprefix $(ENV_DIR), $(ENV_FILES)) \
		$(addprefix $(MAIN_DIR), $(MAIN_FILES)) \
		$(addprefix $(IO_DIR), $(IO_FILES)) \

INC_FILES = minishell.h
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR)%.h, $(INC_FILES))



#####RULES####

all: aux_libraries $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LFLAGS) $(FT_PRINTF) $(LIBFT) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "Compiling: %s                                    \r" $<
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	printf "Starting compilation..."
	@mkdir -p $(OBJ_DIR)

aux_libraries:
	@make -C $(LIBFT_DIR) -s all
	@make -C $(FT_PRINTF_DIR) -s all

# delete just file OBJ_DIR and o file inside
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) -s clean
	@make -C $(FT_PRINTF_DIR) -s clean

# executes clean and deletes the executable
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) -s fclean
	@make -C $(FT_PRINTF_DIR) -s fclean

re: fclean all

compilation_success:
	@echo "▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌"
	@echo "▐----------██████---██████--███--------------███-----------▌"
	@echo "▐---------░░██████-██████--░░░--------------░░░------------▌"
	@echo "▐----------░███░█████░███--████--████████---████-----------▌"
	@echo "▐----------░███░░███-░███-░░███-░░███░░███-░░███-----------▌"
	@echo "▐----------░███-░░░--░███--░███--░███-░███--░███-----------▌"
	@echo "▐----------░███------░███--░███--░███-░███--░███-----------▌"
	@echo "▐----------█████-----█████-█████-████-█████-█████----------▌"
	@echo "▐---------░░░░░-----░░░░░-░░░░░-░░░░-░░░░░-░░░░░-----------▌"
	@echo "▐----------------------------------------------------------▌"
	@echo "▐----------------------------------------------------------▌"
	@echo "▐----------------------------------------------------------▌"
	@echo "▐--█████████--█████---█████-██████████-████------████------▌"
	@echo "▐-███░░░░░███░░███---░░███-░░███░░░░░█░░███-----░░███------▌"
	@echo "▐░███----░░░--░███----░███--░███--█-░--░███------░███------▌"
	@echo "▐░░█████████--░███████████--░██████----░███------░███------▌"
	@echo "▐-░░░░░░░░███-░███░░░░░███--░███░░█----░███------░███------▌"
	@echo "▐-███----░███-░███----░███--░███-░---█-░███----█-░███----█-▌"
	@echo "▐░░█████████--█████---█████-██████████-█████████-█████████-▌"
	@echo "▐-░░░░░░░░░--░░░░░---░░░░░-░░░░░░░░░░-░░░░░░░░░-░░░░░░░░░--▌"
	@echo "▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌"

.PHONY: clean fclean re all aux_libraries compilation_success
