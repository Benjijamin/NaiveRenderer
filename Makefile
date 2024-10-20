WORKDIR=$(CURDIR)
GLFW=$(WORKDIR)/glfw
GLEW=$(WORKDIR)/glew

GLFW_INCLUDE=$(GLFW)/include
GLEW_INCLUDE=$(GLEW)/include
UTILS_INCLUDE=$(WORKDIR)/utils
MATH_INCLUDE=$(WORKDIR)/math
RENDER_INCLUDE=$(WORKDIR)/render
INCLUDES=-I$(WORKDIR)/ -I$(UTILS_INCLUDE) -I$(MATH_INCLUDE) -I$(RENDER_INCLUDE) -I$(GLFW_INCLUDE) -I$(GLEW_INCLUDE) 

GLFW_LIB=$(GLFW)/lib
GLEW_LIB=$(GLEW)/lib
LINKS=-L$(GLFW_LIB) -L$(GLEW_LIB)

UTILS := $(wildcard $(WORKDIR)/utils/*.cpp)
UTILS_OBJECTS := $(UTILS:.cpp=.o)
MATH := $(wildcard $(WORKDIR)/math/*.cpp)
MATH_OBJECTS := $(MATH:.cpp=.o)
RENDER := $(wildcard $(WORKDIR)/render/*.cpp)
RENDER_OBJECTS := $(RENDER:.cpp=.o)

OBJECTS := $(UTILS_OBJECTS) $(MATH_OBJECTS) $(RENDER_OBJECTS)

export INCLUDES

main.exe: main.cpp
	@echo making utils
	@make -C utils
	@echo making math
	@make -C math
	@echo making render
	@make -C render
	@echo making exe
	@g++ -g $(INCLUDES) $(LINKS) $(OBJECTS) main.cpp -lglfw3 -lglew32 -lglu32 -lopengl32 -lgdi32 -o $(WORKDIR)/build/main.exe
	@echo build finished