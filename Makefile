all: dirs
	make -C ./tests
	make -C ./main

tests:
	make -C ./tests

main:
	make -C ./main

dirs:
	@mkdir -p obj

clean:
	make -C ./main clean
	make -C ./tests clean

force: clean all;
