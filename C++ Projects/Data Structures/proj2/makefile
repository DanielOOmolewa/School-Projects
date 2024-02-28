CXX = g++
CXXFLAGS = -Wall

proj2: bNode.o wordTree.o bookTree.o myTest.cpp
	$(CXX) $(CXXFLAGS) bNode.o wordTree.o bookTree.o myTest.cpp -o proj2

bookTree.o: bookTree.h bookTree.cpp bNode.o
    $(CXX) $(CXXFLAGS) -c bookTree.cpp

bNode.o: bNode.h bNode.cpp wordTree.o
    $(CXX) $(CXXFLAGS) -c bNode.cpp

wordTree.o: wordTree.h wordTree.cpp
    $(CXX) $(CXXFLAGS) -c wordTree.cpp

clean:
    rm *.o
    rm *~

run:
    ./proj2




