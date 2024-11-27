CC = g++               # Compiler
FLAGS = -std=c++20     # Compiler flags
TARGET = Test          # Output binary
OBJECTS = Test.o FiniteFunctions.o NormalDistribution.o NegativeCrystalBallDistribution.o CauchyLorentzDistribution.o
LIBS=-I ../../GNUplot/ -lboost_iostreams
#INCLUDES = -I ../../GNUplot
#LIBS = -lboost_iostreams
${TARGET}: ${OBJECTS}
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}
	@make clean

Test.o: Test.cxx FiniteFunctions.h NormalDistribution.h NegativeCrystalBallDistribution.h CauchyLorentzDistribution.h
	${CC} ${FLAGS} ${LIBS} -c Test.cxx

FiniteFunctions.o: FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions.cxx 

NormalDistribution.o: NormalDistribution.cxx NormalDistribution.h
	${CC} ${FLAGS} ${LIBS} -c NormalDistribution.cxx

NegativeCrystalBallDistribution.o: NegativeCrystalBallDistribution.cxx NegativeCrystalBallDistribution.h
	${CC} ${FLAGS} ${LIBS} -c NegativeCrystalBallDistribution.cxx
CauchyLorentzDistribution.o: CauchyLorentzDistribution.cxx CauchyLorentzDistribution.h
	${CC} ${FLAGS} ${LIBS} -c CauchyLorentzDistribution.cxx

clean:
	@rm -f *.o *~

cleantarget:
	@rm -f ${TARGET}
