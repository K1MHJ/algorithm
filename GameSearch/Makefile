.PHONY: all

CC := clang
CXX := clang++
LD := clang++
AR := ar
CFLAGS := -O3 -std=c++20
# CXXFLAGS = $(CFLAGS) -std=c++20 -MD -Wall  -g

SRCDIR := ./src/
OBJDIR := ./obj/
BINDIR := ./bin/
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/ -I/opt/homebrew/Cellar/ncurses/6.5/include/
LDFLAGS := -L/usr/lib -L/usr/local/lib -L/opt/homebrew/Cellar/ncurses/6.5/lib -lncurses

OBJS := $(SRCS:.cpp=.o)

# OBJS 안의 object 파일들 이름 앞에 $(OBJ_DIR)/ 을 붙인다.
OBJECTS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

TARGET := MazeState

all : $(BINDIR)$(TARGET)

run:
	$(BINDIR)$(TARGET)

$(BINDIR)MazeState : $(SRCDIR)main.cpp
	mkdir -p $(BINDIR)
	$(CXX) -o $@ $(CFLAGS) $(INCLUDE) $(LDFLAGS) $^

clean :
	rm -rf ./bin ./obj
