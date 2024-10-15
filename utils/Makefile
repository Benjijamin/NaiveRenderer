OBJS = utils.o ppm.o

all: $(OBJS)

utils.o: utils.cpp utils.h
	@echo making utils
	@g++ -c $(INCLUDES) utils.cpp -o utils.o

ppm.o: ppm.cpp ppm.h
	@echo making ppm
	@g++ -c $(INCLUDES) ppm.cpp -o ppm.o
