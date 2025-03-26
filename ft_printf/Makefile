#variables

NAME = printf.a

SRCDIR = ./src/

INCDIR = ../include/

FILES = ft_flags\
		ft_printchar\
		ft_printf\
		ft_printstr\
		ft_utils\
		ft_printhex\
		ft_printnbr\
		ft_printptr\
		ft_printunsigned\
		ft_printf_itoa

SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))

INC = ft_printf.h

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

#rules
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
