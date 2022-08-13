# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 02:44:46 by het-tale          #+#    #+#              #
#    Updated: 2022/08/13 00:59:55 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    fdf

SRCS    =    *.c gnl/*.c

OBJCT    =    ${SRCS:.c=.o}

FLAGS    =    -Wall -Wextra -Werror -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

RM        =    rm -f

CC        =    gcc

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :
	${RM} ${OBJCT}

fclean : clean
	${RM} ${NAME}

re : fclean all

#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