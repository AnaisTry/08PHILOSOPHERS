# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angassin <angassin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 12:10:21 by angassin          #+#    #+#              #
#    Updated: 2023/06/02 16:15:17 by angassin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------COLORS------------------------------------------

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
BLUE='\033[1;94m'
RED='\033[1;91m'

#-------------------------------VARIABLES---------------------------------------

NAME		= philo

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -pthread

DEBUG		= 0

THREAD_SANI	= 0

SANI		= 0

ifeq ($(THREAD_SANI), 1)
	CFLAGS += -fsanitize=thread
	DEBUG = 1
endif

ifeq ($(SANI, 1))
	CFLAGS += -fsanitize=address 
	DEBUG = 1
endif

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

#--------------------------------SOURCES----------------------------------------

SRC			= $(PHILO_SRC) $(UTILS_SRC)

PHILO_SRC	= main.c init.c #philo.c
UTILS_SRC	= utils.c

OBJ			= $(SRC:.c=.o)

#---------------------------------RULES-----------------------------------------

%o: %c
	@echo $(GRAY)"Compiling...";
	@$(CC) $(CFLAGS)  -Iincludes -c $< -o  $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)


exe: all
	@make -C ./ clean
	@echo "     - Executing $(NAME)... \n"
	@./$(NAME) 5 800 200 200
	@echo "\n     - Done -"

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all exe clean fclean re
