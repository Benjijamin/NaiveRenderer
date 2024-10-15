WORKDIR=$(CURDIR)
GLFW=$(WORKDIR)/glfw

GLFW_INCLUDE=$(GLFW)/include
UTILS_INCLUDE=$(WORKDIR)/utils
MATH_INCLUDE=$(WORKDIR)/math
INCLUDES=-I$(WORKDIR)/ -I$(UTILS_INCLUDE) -I$(MATH_INCLUDE) -I$(GLFW_INCLUDE) 

GLFWLIB=$(GLFW)/lib
LINKS=-L$(GLFWLIB)

UTILS := $(wildcard $(WORKDIR)/utils/*.cpp)
UTILS_OBJECTS := $(UTILS:.cpp=.o)
MATH := $(wildcard $(WORKDIR)/math/*.cpp)
MATH_OBJECTS := $(MATH:.cpp=.o)

OBJECTS := $(UTILS_OBJECTS) $(MATH_OBJECTS)

export INCLUDES

main.exe: main.cpp
	@echo making utils
	@make -C utils
	@echo making math
	@make -C math
	@echo making exe
	@g++ -g $(INCLUDES) $(LINKS) $(OBJECTS) main.cpp -lglfw3 -lgdi32 -o $(WORKDIR)/main.exe
	@echo build finished