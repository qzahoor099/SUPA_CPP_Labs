CC = g++ # Name of compiler
FLAGS = -std=c++20 -w # Compiler flags (the s makes it silent)
TARGET = Test # Executable name
OBJECTS = Test.o FiniteFunctions.o NormalDistribution.o
LIBS = -I ../../GNUplot/ -lboost_iostreams

# First target in Makefile is default
${TARGET}: ${OBJECTS} # Make target from objects
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}
	@make clean

Test.o: Test.cxx FiniteFunctions.h NormalDistribution.h
	${CC} ${FLAGS} ${LIBS} -c Test.cxx

FiniteFunctions.o: FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions.cxx 

NormalDistribution.o: NormalDistribution.cxx NormalDistribution.h
	${CC} ${FLAGS} ${LIBS} -c NormalDistribution.cxx

clean: # No targets just run shell command to remove object files and emacs backups
	@rm -f *.o *~

cleantarget: # Delete the executable
	@rm -f ${TARGET}
