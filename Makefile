CXX = g++
CPP = g++ -c

EXECUTABLE = sea_battle

all: linking clean

linking: main.o game.o battleField.o shipManager.o ship.o 
	$(CXX) main.o game.o battleField.o shipManager.o ship.o -o $(EXECUTABLE)

game.o: game.cpp game.h battleField.h shipManager.h
	$(CPP) game.cpp

battleField.o: battleField.cpp battleField.h shipManager.h ship.h
	$(CPP) battleField.cpp

shipManager.o: shipManager.cpp shipManager.h battleField.h ship.h
	$(CPP) shipManager.cpp

ship.o: ship.cpp ship.h battleField.h shipManager.h
	$(CPP) ship.cpp

main.o: main.cpp game.h
	$(CPP) main.cpp

clean:
	rm -f ./*.o

clear: clean
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) input_file.txt
