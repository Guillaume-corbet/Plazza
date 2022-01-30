##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

NAME	= plazza

CC	= g++

RM	= rm -f

SRCS	= ./src/*.cpp \
		  ./src/Pizza/*.cpp

CPPFLAGS = -I ./
CPPFLAGS += -Wall -Wextra -ldl

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
 T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	  -nrRf $(firstword $(MAKEFILE_LIST)) \
	  ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

 N := x
 C = $(words $N)$(eval N := x $N)
 ECHO = echo " \033[0;32m"`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"\033[0m"
endif

all: clean $(NAME)
	 @$(ECHO)

$(NAME):
	 @echo "\033[0;33m Compiling :\n" $(SRCS)
	 @$(ECHO)
	 @ $(CC) -g3 $(SRCS) -o $(NAME) $(CPPFLAGS) -lpthread 
	 @echo "\033[0;32m Done ! \033[0m"

run: fclean all
	 @sleep 0.1
	 @echo "\033[0;32m Lauching... \033[0m"
	@ ./$(NAME)

valgrind: fclean all
	 @sleep 0.1
	 @echo "\033[0;32m Lauching... \033[0m"
	@ valgrind -v --leak-check=full --show-leak-kinds=all ./$(NAME)

clea:
	@ $(RM) $(GAME)

clear:
	@ $(RM) $(LIBRAIRY)

clean:
	@ $(RM) $(NAME)
	 @echo "\033[0;31m Cleaning. \033[0m" "."".""."
	 @sleep 0.2

fclean:
	@ $(RM) $(NAME)
	 @echo "\033[0;31m Cleaning. \033[0m" "."".""."
	 @sleep 0.2

re: fclean all

.PHONY: all clean fclean re

endif