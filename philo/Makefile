CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

NAME = fdf


FILES = main.c \
philo_rutine.c \
print.c \
utilitis.c \
init.c \
input_check.c 


OBJ = ${FILES:%.c=%.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME} 

${OBJ} : ${FILES}
	${CC} ${CFLAGS} -c ${FILES} 

re :	fclean all

clean :
	${RM} ${OBJ} 

bonus :
	$(MAKE) all ISBONUS=1

fclean : clean
	${RM} ${NAME} 

.PHONY: all clean fclean bonus re
