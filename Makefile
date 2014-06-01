# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/26 19:06:18 by gpetrov           #+#    #+#              #
#    Updated: 2014/06/01 23:08:29 by gpetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lemipc
FILES	= main.c case.c init.c tools.c semaphore.c msgq.c check_if_dead.c \
		  init_shm.c case2.c tools2.c
FILES_G	= main.c mlx.c init_mlx.c print_pixel.c draw_player.c eb_expose_hook.c
SRCS	= $(addprefix srcs/, $(FILES))
SRCS_G	= $(addprefix graph/, $(FILES_G))
OBJS	= $(SRCS:srcs/%.c=.obj/%.o)
OBJS_G	= $(SRCS_G:srcs/%.c=grap/.obj/%.o)
INC		= -I includes -I libft/includes -I /usr/X11/include
FLAGS	= -Wall -Wextra -Werror
LIB		= -L libft -lft -lpthread
LIBMLX	= -L /usr/X11/lib -lmlx -lXext -lX11
CC		= cc

all: $(NAME)

$(NAME): libft_comp create_fold_obj $(OBJS) $(OBJS_G)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)
	@$(CC) $(FLAGS) $(OBJS_G) -o graphique $(INC) $(LIB) $(LIBMLX)
	@echo "\n > \033[36m$(NAME)\033[m project compilation [\033[32mDONE\033[m]\n"

.obj/%.o: srcs/%.c
	@$(CC) -c $< -o $@ $(FLAGS) $(INC)
	@echo -n .

graph/.obj/%.o: graph/%.c
	@$(CC) -c $< -o $@ $(FLAGS) $(INC)

libft_comp:
	@make -C libft

create_fold_obj:
	@mkdir -p .obj
	@mkdir -p graph/.obj

clean:
	@rm -rf .obj
	@rm -rf graph/.obj

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@rm -f graphique
	@echo "fclean : [\033[32mDONE\033[m]"

re: fclean all

gdb: libft_comp
	cc -g $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)
	gdb $(NAME)

.PHONY: all libft_comp create_fold_obj clean fclean re
