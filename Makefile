# -c: Tells the compiler to compile the source file into an object
#	file (.o) rather than an executable.
# $<: The first prerequisite, which here is the .c file from src/.
# -o $@: Specifies the output file name. $@ is a special variable
#	that represents the target, which in this rule is the .o file in $(OBJ_DIR).
# | is 'order-only prerequisites. You use when the dependance has
#	need to exist before to be executed.

###VARIABLES###

# name of the executable
NAME = mini_shell

# compilator and compilation flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lreadline -lncurses

# directories
EXEC_DIR = execution/
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
EXEC_FILES = execution.c exec_built_01.c exec_built_02.c exec_cmd.c exec_heredoc.c
PARS_FILES = parsing.c lexing.c command_block.c
ERR_FILES = error_handle.c free_data.c free_data_utils.c
SIG_FILES = signal_init.c
FILES = $(addprefix $(EXEC_DIR), $(EXEC_FILES)) $(addprefix $(PARS_DIR), $(PARS_FILES)) \
		$(addprefix $(ERR_DIR), $(ERR_FILES)) $(addprefix $(SIG_DIR), $(SIG_FILES)) \
		main.c  utils1.c utils2.c  environment.c in_out_manage.c
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
