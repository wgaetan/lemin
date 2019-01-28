PHONY = all clean fclean re

NAME = lem-in

# **************************************************************************** #
#          PATH                                                                #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LIBFT_PATH = ./libft/

# **************************************************************************** #
#           SRCS                                                               #
# **************************************************************************** #

LIB_NAME = libft.a

SRC_NAME = error_tools.c lem_bit_fields_tools.c lem_bitwise_tools.c \
		   lem_check_data.c lem_detect_line_type.c lem_extract_data.c \
		   lem_get_param.c lem_input_tools.c lem_parse.c \
		   lem_parse_struct_tools.c lem_path_finder.c lem_path_set_tools.c \
		   lem_path_tools.c lem_rooms.c lem_send_ants.c lem_solve.c \
		   lem_stock.c lem_tunnels.c lem_write_ants.c main.c \

INC_NAME = lemin.h

# **************************************************************************** #
#           VAR                                                                #
# **************************************************************************** #

OBJ_NAME= $(SRC_NAME:.c=.o)

INC = $(addprefix $(INC_PATH), $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
LIB = $(addprefix $(LIBFT_PATH), $(LIB_NAME))

# **************************************************************************** #
#           FLAG                         						               #
# **************************************************************************** #

ifndef FLAG
    FLAGS = -Wall -Wextra -Werror
endif

# **************************************************************************** #
#           REGLES                                                             #
# **************************************************************************** #

all : makelib $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ) $(INC) $(LIB)
	@printf "Compiling $(NAME)..."
	@gcc $(FLAGS) -o $@ $(OBJ) $(LIB)
	@printf "\033[32m[OK]\033[0m\n"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) 2> /dev/null

makelib:
	@make -C libft/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@gcc $(FLAGS) -I $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
