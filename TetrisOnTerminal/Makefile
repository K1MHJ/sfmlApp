.HONY: all run
CC := clang
CXX := clang++
LD := clang++
AR := ar
RANLIB :=
CFLAGS := -g -O3 -MP -MMD
CXXFLAGS := $(CFLAGS) -std=c++20 -xc++
SRCDIR := ./
OBJDIR := ./obj/
BINDIR := ./../bin/
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/ -I/opt/homebrew/Cellar/ncurses/6.5/include/
INCLUDE := $(INCLUDE) -I./
INCLUDE := $(INCLUDE) -I$(SRCDIR) 
LDFLAGS := -L/usr/lib -L/usr/local/lib -L/opt/homebrew/Cellar/ncurses/6.5/lib -lncurses

TARGET := $(BINDIR)Tetris

SRC := ./main.cpp ./colors.cpp ./grid.cpp ./position.cpp ./game.cpp ./block.cpp 
SRC := $(SRC)

OBJS  := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o)) 
DEPS  := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.d))

all: $(TARGET)

run:
	$(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LDFLAGS) $(FRAMEWORKS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

debug : $(TARGET)
	@echo "debug $(TARGET)"
	lldb $(TARGET)

clean :
	rm -rf $(BINDIR) $(OBJDIR)

-include $(DEPS)
