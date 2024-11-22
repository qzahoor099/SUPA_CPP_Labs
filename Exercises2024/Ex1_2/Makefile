#this is my makefile, the target is AnalyseData , after doing make , write ./AnalyseData
# I have many other files inside this assignm,ent 2 dont cut my marks for that, it just what i practice to solve it 
#setting the compiler and target files 
CXX = g++
CXXFLAGS = -std=c++20

TARGET = AnalyseData

#adding my files 
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



	
