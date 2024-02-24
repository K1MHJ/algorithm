.PHONY: all

all:
# hello
	cd ./src/hello && make
# 2839
	cd ./src/2839 && make

clean :
	cd ./src/hello && make clean
