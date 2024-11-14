DIR			= .
SRC			= ${DIR}/cub3d.c \
			  ${DIR}/event_handler.c \
			  ${DIR}/image_helper.c \
			  ${DIR}/draw_helper.c \
			  ${DIR}/movement.c \
			  ${DIR}/init.c \
			  ${DIR}/player_helper.c \
			  ${DIR}/ray_casting.c 


OBJS		= ${SRC:.c=.o}

INCLUDE		= ./header

NAME	    = cub3d

AR			= ar rcs

CC			= cc
#CC			= cc -Wall -Wextra -Werror
  
LIBFT_DIR	= ./libft
LIBFT		= ${LIBFT_DIR}/libft.a

MINILIBX_DIR = ./minilibx-linux
LIBMLX 	= ${MINILIBX_DIR}/libmlx.a
LIBMLX_LINUX = ${MINILIBX_DIR}/libmlx_Linux.a

LFLAGS      =  -Lminilibx-linux -Lmlx-Linux -lX11 -lXext -lm

all: ${NAME}

%.o: %.c
			${CC} -c -I ${INCLUDE}  $< -o ${<:.c=.o} 

${NAME}: ${OBJS} ${LIBFT}
			cc -g -o ${NAME} ${OBJS} ${LIBFT} ${LIBMLX} ${LIBMLX_LINUX} $(LFLAGS)	

${LIBFT}:
		make bonus -C ${LIBFT_DIR}

clean:
	make clean -C ${LIBFT_DIR}
	rm -f ${OBJS}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
