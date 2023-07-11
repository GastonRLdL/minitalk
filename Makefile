# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: groman-l <groman-l@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 11:11:23 by groman-l          #+#    #+#              #
#    Updated: 2023/07/11 15:15:05 by groman-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~VARIABLES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
NAME = minitalk
CLIENT_NAME = client
SERVER_NAME = server
CC = gcc
RM = rm -rf
LIBC = ar -rcs
FLAGS = -Wall -Wextra -Werror -g

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SORUCES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
SRC = client.c server.c
LIBFT = ./libft/
L_SRC = ./src
L_LIB = ./libft/libft.a
INC =   -I ./inc/\
        -I ./libft/\

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DIRECTORIES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
D_OBJ = $(L_SRC)/obj
OBJ_SERVER = $(addprefix $(D_OBJ)/, $(SRC:.c=.o))
OBJ_CLIENT = $(addprefix $(D_OBJ)/, $(SRC:.c=.o))
DEP_SERVER = $(addprefix $(D_OBJ)/, $(SRC:.c=.d))
DEP_CLIENT = $(addprefix $(D_OBJ)/, $(SRC:.c=.d))

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAKE RULES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
all: dir
	$(MAKE) $(CLIENT_NAME) --no-print-directory
	$(MAKE) $(SERVER_NAME) --no-print-directory

-include $(DEP_CLIENT)
-include $(DEP_SERVER)

dir:
	@make -C $(LIBFT) --no-print-directory
	@mkdir -p $(D_OBJ)

$(D_OBJ)/%.o: $(L_SRC)/%.c
	@$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)

$(CLIENT_NAME): $(OBJ_CLIENT)
	@$(CC) $(FLAGS) $(D_OBJ)/client.o $(L_LIB) -o $(CLIENT_NAME) $(INC)

$(SERVER_NAME): $(OBJ_SERVER)
	@$(CC) $(FLAGS) $(D_OBJ)/server.o $(L_LIB) -o $(SERVER_NAME) $(INC)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLEAN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
.PHONY: clean fclean re

fclean: clean
	$(RM) $(NAME) $(CLIENT_NAME) $(SERVER_NAME)
	@make fclean -C $(LIBFT) --no-print-directory

clean:
	$(RM) $(D_OBJ)
	@make clean -C $(LIBFT) --no-print-directory

re: fclean all