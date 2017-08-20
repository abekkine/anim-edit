TARGET = animEdit
SRC = $(wildcard src/*.cpp) main.cpp
OBJ = $(SRC:%.cpp=%.o)
CXX = g++

CFLAGS = -g -std=c++11 -I./inc -I./events -Wall -Wextra -Werror -Wfatal-errors -pthread
LIBS = -lboost_system -lGL -lglfw

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
