CC=g++
CFLAGS=-c -Wall
SOURCES= main.cpp Vect.cpp Vertex.cpp Branch.cpp Plant.cpp Data.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(OTHERFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o core
