CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lopencv_highgui -lopencv_core
SOURCES=template.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=face

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
