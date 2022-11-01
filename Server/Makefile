NAME			=	proxy

CC				=	clang++

CDEBUG			=	 -Wall -Wextra -Werror -std=c++98

SRC				=	main.cpp Server.cpp Client.cpp Utils.cpp

OBJ				=	$(SRC:.cpp=.o)
OBJ_DIR			=	./objs/
OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ))

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					@$(CC) -o $@ $^
					@echo "\033[32m"Make DONE

$(OBJ_DIR)%.o	:	%.cpp
					@mkdir -p $(OBJ_DIR)
					@$(CC) -c $< -o $@

.PHONY			:	all fclean clean re

clean			:
				@rm -rf $(OBJ_DIR)
				@echo "\033[32m"clean DONE

fclean			:	clean
				@rm -rf $(NAME) log.txt
				@echo "\033[32m"fclean DONE
