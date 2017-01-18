CC=g++
CFLAGS=-c -Wall -ggdb -I. -O3 -std=c++14
LDFLAGS=-lpthread -lcgicc
SOURCES=helloWorld.cpp
EXECUTABLE=cgi-bin/helloWorld.cgi

OBJECTS=$(SOURCES:.cpp=.o)

FLAGS= -Iinclude

all: $(SOURCES) $(EXECUTABLE)


# These next lines do a bit of magic found from http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# Essentially it asks the compiler to read the .cpp files and generate the needed .h dependencies.
# This way if any .h file changes the correct .cpp files will be recompiled
depend: .depend

.depend:	$(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
# End .h file magic

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
	rm -f ./.depend
	rm -f testrunner
	rm -f testrunner.cpp

	# CXX Testing
CXXTESTGEN = CxxTest/bin/cxxtestgen

test: testrunner
	./testrunner

testrunner: testrunner.cpp $(OBJECTSTEST)
	g++ -I. -ICxxTest/ -o testrunner $(OBJECTSTEST) testrunner.cpp

testrunner.cpp: $(HEADERS) $(SOURCES) $(TESTS)
	$(CXXTESTGEN) --error-printer -o testrunner.cpp $(TESTS)

