NAME    = er_to_afn

CC      = gcc
CFLAGS  = -Wall -W -pedantic -I includes -I src

SRCDIR  = src
OBJDIR  = obj

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
