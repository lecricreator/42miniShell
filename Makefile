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
SRC_DIR= ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./include/
LIBFT_DIR = ./libft/
FT_PRINTF_DIR = ./ft_printf/

# custom libraries
LIBFT = $(LIBFT_DIR)libft.a
FT_PRINTF = $(FT_PRINTF_DIR)printf.a

# files
FILES = main.c parsing.c utils.c error_handle.c lexing.c execution.c exec_built.c execution_utils.c
INC_FILES = minishell.h
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR)%.h, $(INC_FILES))



#####RULES####

all: aux_libraries $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(FT_PRINTF) $(LIBFT) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

aux_libraries:
	make -C $(LIBFT_DIR) all
	make -C $(FT_PRINTF_DIR) all

# delete just file OBJ_DIR and o file inside
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

# executes clean and deletes the executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

compilation_success:
	@echo "▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌"
	@echo "▐-██████---██████--███--------------███-----------▌"
	@echo "▐░░██████-██████--░░░--------------░░░------------▌"
	@echo "▐-░███░█████░███--████--████████---████-----------▌"
	@echo "▐-░███░░███-░███-░░███-░░███░░███-░░███-----------▌"
	@echo "▐-░███-░░░--░███--░███--░███-░███--░███-----------▌"
	@echo "▐-░███------░███--░███--░███-░███--░███-----------▌"
	@echo "▐-█████-----█████-█████-████-█████-█████----------▌"
	@echo "▐░░░░░-----░░░░░-░░░░░-░░░░-░░░░░-░░░░░-----------▌"
	@echo "▐-------------------------------------------------▌"
	@echo "▐-------------------------------------------------▌"
	@echo "▐-------------------------------------------------▌"
	@echo "▐--█████████--█████---█████-██████████-████--████-▌"
	@echo "▐-███░░░░░███░░███---░░███-░░███░░░░░█░░███-░░███-▌"
	@echo "▐░███----░░░--░███----░███--░███--█-░--░███--░███-▌"
	@echo "▐░░█████████--░███████████--░██████----░███--░███-▌"
	@echo "▐-░░░░░░░░███-░███░░░░░███--░███░░█----░███--░███-▌"
	@echo "▐-███----░███-░███----░███--░███-░---█-░███--░███-▌"
	@echo "▐░░█████████--█████---█████-██████████-█████-█████▌"
	@echo "▐-░░░░░░░░░--░░░░░---░░░░░-░░░░░░░░░░-░░░░░-░░░░░-▌"
	@echo "▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌"

.PHONY: clean fclean re all aux_libraries compilation_success
