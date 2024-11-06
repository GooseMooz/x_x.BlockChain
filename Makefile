CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread
LIBS = -lssl -lcrypto

SOURCES = main.cpp Block.cpp BlockChain.cpp Transaction.cpp Node.cpp
HEADERS = Block.h BlockChain.h Transaction.h Node.h

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = blockchain_node

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp $(HEADERS)
    $(CXX) $(CXXFLAGS) -c $<

clean:
    rm -f $(OBJECTS) $(EXECUTABLE)

run: all
    ./$(EXECUTABLE)

