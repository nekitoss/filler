UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CC = gcc
endif
ifeq ($(UNAME), Linux)
	CC = c99
endif

FLAGS = -Wall -Wextra -Werror

NAME = filler

SRC = main.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

INC = -I ./ -I ./libft/

LIB = -L ./libft -lft

LIBMAKE = make -C libft/

# LIBINC = -I libft/libft.h -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIBMAKE) all
	@$(CC) $(FLAGS) $(INC) $(LIB) $(OBJ) -o $(NAME)
	@echo  "\033[32mCompiled and created filler binary\033[0m"

%.o: %.c
	@$(CC) $(INC) $(FLAGS) -c -o $@ $<

clean: libclean
	@rm -f $(OBJ)
	@echo "\033[01;31mFiller object files deleted\033[0m"

fclean: libfclean clean
	@rm -rf *.dSYM
	@rm -f $(NAME) a.out
	@echo "\033[01;31mFiller binary file deleted\033[0m"

re: fclean all

liball:
	@$(LIBMAKE) all

libclean:
	@$(LIBMAKE) clean
libfclean:
	@$(LIBMAKE) fclean

libre:
	@$(LIBMAKE) re

debug:
	@$(CC) $(FLAGS) -g $(LIBOBJ) $(INC) ./libft/libft.h main.c
	@echo  "\033[1;33m DEBUG compilation finished\033[0m"