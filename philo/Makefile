# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 17:39:23 by jberredj          #+#    #+#              #
#    Updated: 2021/12/30 23:15:40 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	clang
OPTI			=	-O3
CFLAGS			=	-Wall -Werror -Wextra $(OPTI)
LDFLAGS			= 	-lpthread

SRC_DIR			= 	.
INC_DIR			=	.
OBJ_DIR			=	objs/


###############################################################################
##								Source files								 ##
###############################################################################

MAIN			=	args.c error_args.c ft_atoi.c ft_memset.c main.c\
					ft_put_fd.c table.c philosopher.c start_sim.c utils.c
MAIN_SRCS		=	$(MAIN)
MAIN_OBJS		=	$(addprefix objs/, $(subst /,., $(MAIN:.c=.o)))


STRUCTS			=	structs.h
HEADERS			=	$(STRUCTS)\
					philosophers.h

SRCS			=	$(MAIN_SRCS)
OBJS			=	$(MAIN_OBJS)

MODULE			=	main

###############################################################################
##							Color output char								 ##
###############################################################################
BLUE			=\033[0;34m
NC				=\033[0m
LIGHT_PURPLE	=\033[1;35m
GREEN			=\033[0;32m
RED				=\033[0;31m

###############################################################################
## 							Mandatory recipes								 ##
###############################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)executable$(NC)\n"
	$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $(LDFLAGS) -o $(NAME)
	printf "$(GREEN)Completed$(NC)\n"

clean:
	printf "$(RED)Removing objects files$(NC)\n"
	rm -rf objs
	rm -rf *.o;

fclean: clean
	printf "$(RED)Removing $(LIGHT_PURPLE)$(NAME) \
	$(RED)executable\nRemoving libraries$(NC)\n"	
	rm -rf $(NAME)
	rm -rf $(LIBS)

re: fclean all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

define COMPILE
	find ./objs/ -type f -exec touch {} +
	$(foreach source,$?, \
	printf "$(YELLOW)[..]   $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))\
$(NC)\n"; \
	$(CC) -I $(INC_DIR) $(CFLAGS) -c $(source) -o \
$(addprefix $(OBJ_DIR), $(subst /,.,$(subst srcs/,,$(source:.c=.o)))) ; \
	if [ $$? -ne "0" ];\
	then \
		exit 1;\
	fi; \
	norminette $(source) > /dev/null ;\
	if [ $$? -ne "0" ];\
	then \
		printf "\033[F$(RED)[NORM]$(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	else \
		printf "\033[F$(GREEN)[OK]  $(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	fi;)
endef

main: $(OBJ_DIR) $(MAIN_OBJS)
$(MAIN_OBJS): $(MAIN_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)main $(BLUE)functions$(NC)\n"
	$(COMPILE)

ffclean: fclean
	make -C libft fclean

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))

debug: CFLAGS = -g -D DEBUG 
debug: all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind:
	valgrind  --trace-children=yes --suppressions=./ignoreliberror  --leak-check=full --show-leak-kinds=all ./$(NAME)

.SILENT:

commit_all_files: ffclean
	git add .
	git commit

###############################################################################
## 								Norm recipe									 ##
###############################################################################

norm:
	printf "$(BLUE)Checking norm$(NC)\n"
	norminette $(SRCS) $(addprefix $(INC_DIR)/, $(HEADERS)) \
	; if [ "$$?" -ne "0" ]; then printf "$(RED)NORM ERROR$(NC)\n"; \
	else printf "$(GREEN)NORM OK$(NC)\n";fi
