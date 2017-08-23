TARGET = animEdit
SRC = $(wildcard src/*.cpp) main.cpp
OBJ = $(SRC:%.cpp=%.o)
CXX = g++

CFLAGS  = -g -std=c++11
CFLAGS += -I/usr/include/freetype2 -I./inc -I./events
CFLAGS += -Wall -Wextra -Werror -Wfatal-errors
LIBS = -lboost_system -lGL -lglfw -lftgl -pthread

all: version application

application: $(OBJ)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) -c -o $*.o $<

version:
	$(RM) Version.h
	bash version.sh

clean:
	$(RM) core* $(TARGET) $(OBJ) Version.h
