
compile:
	mkdir -p build; cd build; cmake ..; make

test:
	cd build; ./tests/tests

clean:
	cd build && make clean"

all: compile test
