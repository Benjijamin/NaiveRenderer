OBJS = sceneobject.o mesh.o

all: $(OBJS)

sceneobject.o: sceneobject.cpp sceneobject.h
	@echo making sceneobject
	@g++ -c $(INCLUDES) sceneobject.cpp -o sceneobject.o

mesh.o: mesh.cpp mesh.h
	@echo making mesh
	@g++ -c $(INCLUDES) mesh.cpp -o mesh.o