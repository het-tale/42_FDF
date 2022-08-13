# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 02:44:46 by het-tale          #+#    #+#              #
#    Updated: 2022/08/13 15:37:23 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    fdf

SRCS    =    parsing/lines.c parsing/map_parsing.c parsing/pars_utils.c parsing/split_utils.c parsing/gnl/ft_atoi.c parsing/gnl/ft_split.c parsing/gnl/ft_strremove.c parsing/gnl/ft_substr.c \
			parsing/gnl/get_next_line.c parsing/gnl/get_next_line_utils.c src/keys.c src/main.c drawing/draw_utils.c drawing/draw.c drawing/window.c

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
