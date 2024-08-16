.PHONY: all run
CC := clang
CXX := clang++
LD := clang++
AR := ar
RANLIB :=
CFLAGS := -g -O0 -Wall -MP -MMD
CXXFLAGS := $(CFLAGS) -std=c++20 -xc++
SRCDIR := ./src
OBJDIR := ./obj
BINDIR := ./bin
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/ 
INCLUDE := $(INCLUDE) -I/opt/homebrew/Cellar/sfml/2.6.1/include/
INCLUDE := $(INCLUDE) -I./vendor/spdlog/include/
INCLUDE := $(INCLUDE) -I./src 
INCLUDE := $(INCLUDE) -I./src/App -I./src/Core -I./src/Debug 
INCLUDE := $(INCLUDE) -I./src/Utils -I./src/MacOs -I./src/Events -I./src/UI
INCLUDE := $(INCLUDE) -I./src/SFML -I./src/Renderer

LIBS := -lm
TARGET := ./bin/App
SFMLLIB := -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS := -L/usr/lib -L/usr/local/lib $(SFMLLIB)
PCH_OUT := $(OBJDIR)/pch.gch
PCH_SRC := $(SRCDIR)/pch.cpp
PCH_HEADERS := $(SRCDIR)/pch.h

SRC := 
SRC := $(SRC) App/MyApp.cpp App/MyLayer.cpp
SRC := $(SRC) ./Core/Application.cpp ./Core/Layer.cpp ./Core/LayerStack.cpp ./Core/Log.cpp ./Core/Window.cpp
SRC := $(SRC) ./MacOs/MacOsWindow.cpp ./MacOs/MacOsInput.cpp ./MacOs/MacOsPlatformUtils.cpp
SRC := $(SRC) ./SFML/SfmlContext.cpp ./SFML/SfmlRendererAPI.cpp
SRC := $(SRC) ./Renderer/GraphicsContext.cpp ./Renderer/RenderCommand.cpp ./Renderer/Renderer.cpp ./Renderer/RendererAPI.cpp
SRC := $(SRC)

OBJS  := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o)) 
DEPS  := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.d))

all: $(TARGET)

run:
	$(TARGET)

$(TARGET): $(OBJS)
	@echo '$$'LDFLAGS is $(LDFLAGS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LDFLAGS) $(FRAMEWORKS)

$(PCH_OUT): $(PCH_SRC) $(PCH_HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -x c++-header

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

$(OBJDIR)/%.o: %.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

debug : $(TARGET)
	@echo "debug $(TARGET)"
	lldb $(TARGET)

clean :
	rm -rf $(BINDIR) $(OBJDIR) *.json *.log

-include $(DEPS)
