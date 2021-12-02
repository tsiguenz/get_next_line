# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 12:23:38 by tsiguenz          #+#    #+#              #
#    Updated: 2021/12/02 16:44:45 by tsiguenz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=200
FSAN = -fsanitize=address
SRC = get_next_line.c get_next_line_utils.c
NAME = gnl

comp:
	@${CC} ${FLAGS} -o ${NAME} ${SRC}
	@./${NAME}

fsan:
	@${CC} ${FLAGS} ${FSAN} -o ${NAME} ${SRC}
	@./${NAME}

db:
	@${CC} ${FLAGS} -g -o ${NAME} ${SRC}
	@lldb ${NAME}
.PHONY: comp exec
