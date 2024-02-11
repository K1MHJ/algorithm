.PHONY: all run
CC := clang
CXX := clang++
LD := clang++
AR := ar
RANLIB :=
CFLAGS := -g -O2 -Wall
CXXFLAGS := $(CFLAGS) -std=c++20

SRCDIR := ./
OBJDIR := $(ROOT)/obj/$(TARGET)
BINDIR := $(ROOT)/bin
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/
INCLUDE := $(INCLUDE)
LIBS := -lm
DEFINES := 
TARGETPATH := $(BINDIR)/$(TARGET)
LDFLAGS     := -L/usr/lib -L/usr/local/lib

# Make 할 소스 파일들
# wildcard 로 SRC_DIR 에서 *.cc 로 된 파일들 목록을 뽑아낸 뒤에
# notdir 로 파일 이름만 뽑아낸다.
# (e.g SRCS 는 foo.cc bar.cc main.cc 가 된다.)
# SRCS = $(notdir $(wildcard $(SRCDIR)/*.cpp))

OBJS = $(SRCS:.cpp=.o)

# OBJS 안의 object 파일들 이름 앞에 $(OBJ_DIR)/ 을 붙인다.
OBJECTS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

all: $(TARGETPATH)

run:
	$(TARGETPATH)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -MD -o $@ -c $<
	

$(TARGETPATH): $(OBJECTS)
	@echo '$$'LDFLAGS is $(LDFLAGS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LDFLAGS)


debug : $(TARGETPATH)
	@echo "debug $(TARGETPATH)"
	lldb $(TARGETPATH)

clean :
	rm -rf $(TARGETPATH) $(OBJDIR)

-include $(DEPS)
