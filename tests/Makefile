COMPILER = gcc
TESTS = ../run_tests

CFLAGS += -Wall -I../include
LDFLAGS +=

# Test srcs
TSRCS := sudoku.c \
	tests.c

# Test objs
TOBJS := $(TSRCS:%.c=../obj/%.o)

all: $(TESTS)

$(TESTS) : $(TOBJS) $(OBJS)
	@echo Linking tests
	@$(COMPILER) $(CFLAGS) $(TOBJS) $(LDFLAGS) -o $(TESTS) 

$(TOBJS) : ../obj/%.o : ../src/%.c
	@echo Compiling tests
	@$(COMPILER) $(CFLAGS) -c $< -o $@

force: clean all;

clean:
	rm -f $(TESTS)
	rm -f $(TOBJS)
