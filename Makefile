# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msloot <msloot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 19:19:04 by msloot            #+#    #+#              #
#    Updated: 2024/12/08 16:44:24 by adelille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell
CC = 	cc
RM = 	rm -rf

CFLAGS =	-Wall -Werror -Wextra
CFLAGS +=	-g
# CFLAGS +=	-fsanitize=address

ASMFLAGS =	-MMD -MP
ASMINC =	-I./inc/

# LDFLAGS =
LDLIBS =	-lreadline

# **************************************************************************** #
#	MAKEFILE	#

MAKEFLAGS += --silent

SHELL := bash

B =		$(shell tput bold)
I =		$(shell tput sitm)

BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)

D =		$(shell tput sgr0)
CLR =	$(shell tput el 1)

PRIMARY =	$(shell tput setaf 13)
SECONDARY =	$(GRE)

PROGRESS_START =	$(PRIMARY)▐
PROGRESS_END =		$(PRIMARY)▌
# PROGRESS_EMPTY =	-
PROGRESS_FILL =		$(SECONDARY)█

# **************************************************************************** #
#	LIBRARY	#

LIBFT_PATH =	./libft/
LOCAL_LIB =		$(LIBFT_PATH)libft.a
ASMINC +=		-I$(LIBFT_PATH)inc/

LOCAL_LIB_PATH =	$(sort $(dir $(LOCAL_LIB)))

# **************************************************************************** #
#	SOURCE	#

SRC_PATH =	./src/
OBJ_PATH =	./obj/

SRC_NAME =	main.c signals.c loop.c prompt.c \
			parse/parse.c \
			parse/is_expression_separator.c parse/expression_len.c \
			parse/extract_args/extract_args.c \
			parse/extract_args/extract_single_quote.c \
			parse/extract_args/extract_double_quote.c \
			arr.c \
			test.c \
			dispatch.c find_env.c envdup.c \
			error.c \
			builtin/cd.c builtin/echo.c builtin/env.c builtin/b_exec.c builtin/pwd.c \
			builtin/unset.c \

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

TEST_NAME = test
TEST_OBJ_PATH =	./obj/test/
TEST_OBJ_NAME =	$(filter-out main.o, $(OBJ_NAME))
TEST_OBJ =	$(addprefix $(TEST_OBJ_PATH), $(TEST_OBJ_NAME))

# *************************************************************************** #

define	progress_bar
	@printf "$(PROGRESS_START)$(D)"
	@i=0
	@while [[ $$i -lt $(words $(SRC)) ]] ; do \
		printf " " ; \
		((i = i + 1)) ; \
	done
	@printf "$(D)$(PROGRESS_END)$(D)\r$(PROGRESS_START)$(D)"
endef

name = 0

# *************************************************************************** #
#	RULES	#

all:		$(LOCAL_LIB) launch $(NAME)
	@if [ $(name) -ne 0 ]; then \
		printf "\n$(B)$(PRIMARY)─╴$(NAME) compiled$(D)\n"; \
	else \
		printf "\n$(B)$(PRIMARY)─╴$(D)$(B)$(I)nothing to do$(D)\n"; \
	fi

launch:
	$(call progress_bar)

$(NAME):	$(LOCAL_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LOCAL_LIB) $(LDLIBS) -o $(NAME)
	@$(eval name=1)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(ASMFLAGS) $(ASMINC) -c $< -o $@
	@printf "$(D)$(PROGRESS_FILL)$(D)"

$(TEST_OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(ASMFLAGS) $(ASMINC) -DTEST=1 -c $< -o $@

$(LOCAL_LIB):
	@$(MAKE) -C $(dir $@)

$(TEST_NAME):		$(LOCAL_LIB) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_OBJ) $(LOCAL_LIB) $(LDLIBS) -o $(TEST_NAME)
	./$(TEST_NAME)

clean:	$(addsuffix .clean, $(LOCAL_LIB_PATH))
	@$(RM) $(OBJ_PATH) $(TEST_OBJ_PATH)
	@echo "$(B)cleared$(D)"

%.clean:
	@$(MAKE) clean -C $*

fclean:		clean $(addsuffix .fclean, $(LOCAL_LIB_PATH))
	@$(RM) $(NAME)

%.fclean:
	@$(MAKE) fclean -C $*

re:			fclean all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re

# **************************************************************************** #
