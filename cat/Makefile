NAME = cat

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = cat.c
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
