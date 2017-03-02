CXX=g++
CFLAGS=-lopencv_imgcodecs -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_xfeatures2d

jodelMatcher.o:
	$(CXX) -c -o jodelMatcher.o jodelMatcher.cpp

jodelMatcher: jodelMatcher.o
	$(CXX) -o jodelMatcher jodelMatcher.o $(CFLAGS)

all: jodelMatcher
