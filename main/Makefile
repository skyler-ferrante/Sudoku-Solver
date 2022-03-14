COMPILER = gcc
PROJECT = ../sudoku

CFLAGS += -Wall -I../include
LDFLAGS +=

# Normal srcs
SRCS := sudoku.c \
	main.c

# Normal objs
OBJS := $(SRCS:%.c=../obj/%.o)

all: $(PROJECT)

$(PROJECT) : $(OBJS)
	@echo Linking main
	@$(COMPILER) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROJECT) 

$(OBJS) : ../obj/%.o : ../src/%.c
	@echo Compiling main
	@$(COMPILER) $(CFLAGS) -c $< -o $@

force: clean all;

clean:
	rm -f $(OBJS)
	rm -f $(PROJECT)
