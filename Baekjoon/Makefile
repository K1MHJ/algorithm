.PHONY: all

CC := clang
CXX := clang++
LD := clang++
AR := ar
CFLAGS := -g -O2 -Wall -std=c++20
# CXXFLAGS = $(CFLAGS) -std=c++20 -MD 

SRCDIR := ./src/
OBJDIR := ./obj/
BINDIR := ./bin/
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/
LDFLAGS := -L/usr/lib -L/usr/local/lib

OBJS := $(SRCS:.cpp=.o)

# OBJS 안의 object 파일들 이름 앞에 $(OBJ_DIR)/ 을 붙인다.
OBJECTS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

all :

8407: $(SRCDIR)8407.cpp
	mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)$@ $(CFLAGS) $(INCLUDE) $(LDFLAGS) $^

clean :
	rm -rf ./bin ./obj
