.PHONY: all
SRC := 1011.cpp


CC := clang
CXX := clang++
LD := clang++
AR := ar
CFLAGS := -g
CXXFLAGS = $(CFLAGS) -std=c++17 -c

SRCDIR := ./src/
OBJDIR := ./obj/
BINDIR := ./bin/
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/
LDFLAGS := -L/usr/lib -L/usr/local/lib -lgtest_main -lgtest

OBJS  := $(addprefix $(OBJDIR), $(SRC:.cpp=.o)) 
DEPS  := $(addprefix $(OBJDIR), $(SRC:.cpp=.d))

TARGET := app 

all : $(BINDIR)$(TARGET)
run : 
	$(BINDIR)$(TARGET)

$(BINDIR)$(TARGET): $(OBJS)
	@echo '$$'LDFLAGS is $(LDFLAGS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)/%.cpp
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $<

clean :
	rm -rf ./bin ./obj
