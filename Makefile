.PHONY: all

all: hello

hello:
	cd ./src/hello && make

clean :
	cd ./src/hello && make clean
