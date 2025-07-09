NAME := philo
CC := cc
CFLAG :=  -Wall -Wextra -Werror
RM := rm -f

INCLUDE := -I includes
SRCS_DIR := src
OBJS_DIR := obj

SRCS := $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/parse.c \
		$(SRCS_DIR)/init_utils.c 
OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)


all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAG) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@

clean:
		@$(RM) -r $(OBJS_DIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
