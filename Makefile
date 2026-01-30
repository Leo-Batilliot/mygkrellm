##
## EPITECH PROJECT, 2026
## G-PDG-300-LIL-3-1-PDGD04-51
## File description:
## Makefile
##

# FILES
SRC	=	src/main.cpp \
		src/sfml/SfmlDisplay.cpp \
		src/sfml/Display.cpp \
		src/sfml/Inputs.cpp \

# COLORS
RED=\033[31m
GREEN=\033[32m
WHITE=\033[37m
BOLD=\033[1m
RESET=\033[0m

# VARIABLES
OBJ	=	$(SRC:.cpp=.o)
NAME = MyGKrellm

# COMPILER
CC	=	g++
CFLAGS	=	-std=c++20 -Wall -Wextra -Werror -I src/
SFMLFLAGS = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system) -lncurses

# PRINT COMPILATION
%.o: %.cpp
	@echo "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo "$(WHITE)$(BOLD)\t[COMPILATION]$(RESET)"

# LINKING
$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(SFMLFLAGS)
	@echo "$(WHITE)$(BOLD)[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"

# CLEAN OBJECT FILES
clean:
	@found=0; \
	for file in $(OBJ); do \
		if [ -f "$$file" ]; then \
			found=1; \
			break; \
		fi; \
	done; \
	if [ $$found -eq 1 ]; then \
		echo "$(WHITE)$(BOLD)\t[CLEANING OBJ FILES]$(RESET)"; \
		for file in $(OBJ); do \
			if [ -f "$$file" ]; then \
				echo "$(RED)$(BOLD)[REMOVED]:\t$(RESET)$(RED)$$file$(RESET)"; \
				rm -f "$$file"; \
			fi; \
		done; \
	fi


# CLEAN BINARY AND OBJECT FILES
fclean:
	@if [ -f "$(NAME)" ]; then \
		echo "$(WHITE)$(BOLD)\t[CLEANING BINARY]$(RESET)"; \
		echo "$(RED)$(BOLD)[REMOVED]:\t$(RESET)$(RED)$(NAME)$(RESET)"; \
		rm -f $(NAME); \
	fi
	@$(MAKE) clean -s


# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all
