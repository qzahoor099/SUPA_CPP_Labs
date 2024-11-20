CXX = g++
CXXFLAGS = -std=c++20

TARGET = AnalyseData

# Files
SOURCES = AnalyseData.cxx CustomFunctions.cxx
HEADERS = CustomFunctions.h
OBJECTS = $(SOURCES:.cxx=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cxx $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)
