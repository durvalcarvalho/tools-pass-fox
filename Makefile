TARGET = tools-pass-fox
CXX = g++ -std=c++17
DEBUG = -g
OPT = -O0
WARN = -Wall
CXXFLAGS = $(DEBUG) $(OPT) $(WARN)
LD = g++
OBJS = main.o tools-pass-fox.o

all: $(OBJS)
		$(LD) -o $(TARGET) $(OBJS)
		@rm -rf *.o

main.o: main.cpp
		$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

tools-pass-fox.o: tools-pass-fox.cpp
		$(CXX) -c $(CXXFLAGS) tools-pass-fox.cpp -o tools-pass-fox.o
