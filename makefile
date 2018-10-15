CC=g++
CFLAGS=-c -Wall
LDFLAGS=`pkg-config --cflags glfw3`
OTHERFLAGS=`pkg-config --static --libs glfw3` -lGL -lGLEW -lSOIL
SOURCES=  Data.cpp Plant.cpp Vect.cpp Branch.cpp Vertex.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(OTHERFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o core
