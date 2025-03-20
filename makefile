# -c: Tells the compiler to compile the source file into an object
#	file (.o) rather than an executable.
# $<: The first prerequisite, which here is the .c file from src/.
# -o $@: Specifies the output file name. $@ is a special variable
#	that represents the target, which in this rule is the .o file in $(OBJ_DIR).
# | is 'order-only prerequisites. You use when the dependance has
#	need to exist before to be executed.
GG = gcc

FLAGS = -Wall -Werror -Wextra -lreadline -lncurses
FLAGS_DEBUG = -g
PATH_SRC = src/
OBJ_DIR = target
INCLUDE = -Iinclude
LIBRARY =

SRC_SRC = \
	$(PATH_SRC)main.c \
	# $(PATH_SRC)split.c \
	# $(PATH_SRC)utils1.c \
	# $(PATH_SRC)utils2.c \
	# $(PATH_SRC)error.c \
	# $(PATH_SRC)swap_push.c \
	# $(PATH_SRC)reverse.c \
	# $(PATH_SRC)delete_file.c \
	# $(PATH_SRC)verif_init.c \
	# $(PATH_SRC)linked_list.c \
	# $(PATH_SRC)init.c \
	# $(PATH_SRC)freedom.c \
	# $(PATH_SRC)ps3.c \
	# $(PATH_SRC)ps5.c \
	# $(PATH_SRC)ps6_more.c \
	# $(PATH_SRC)sort_index.c \

#SRC:src/%.c recover all c file || move all c file in o
OBJ_SRC = $(patsubst $(PATH_SRC)%.c, $(OBJ_DIR)/%.o, $(SRC_SRC))

NAME = ./mini_shell

all: $(NAME)

# create a file ar for archiver / rcs r for replace c to create sindex library (.o)
$(NAME): $(OBJ_SRC) | $(OBJ_DIR)
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
	$(GG) $(FLAGS) $(FLAGS_DEBUG) $(OBJ_SRC) $(LIBRARY) -o $(NAME)

# create .o file in PATH_SRC
$(OBJ_DIR)/%.o: $(PATH_SRC)%.c | $(OBJ_DIR)
	$(GG) $(FLAGS) $(FLAGS_DEBUG) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# delete just file OBJ_DIR and o file inside
clean:
	rm -rf $(OBJ_DIR)

# delete file OBJ_DIR and o file inside and NAME file a
fclean: clean
	rm -f $(NAME) $(TEST)

re : fclean all
