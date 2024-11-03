CXX = g++
CPP = g++ -c

all: linking clean

linking: main.o gameField.o shipManager.o ship.o exception.o abilityManager.o doubleDamage.o scanner.o bombard.o
	$(CXX) main.o gameField.o shipManager.o ship.o exception.o abilityManager.o doubleDamage.o scanner.o bombard.o -o Battleship

gameField.o: gameField.cpp shipManager.h ship.h
	$(CPP) gameField.cpp

shipManager.o: shipManager.cpp gameField.h ship.h exception.h
	$(CPP) shipManager.cpp

ship.o: ship.cpp gameField.h shipManager.h
	$(CPP) ship.cpp

exception.o: exception.cpp exception.h
	$(CPP) exception.cpp

abilityManager.o: abilityManager.cpp abilityManager.h
	$(CPP) abilityManager.cpp

doubleDamage.o: doubleDamage.cpp doubleDamage.h ability.h
	$(CPP) doubleDamage.cpp

scanner.o: scanner.cpp scanner.h ability.h
	$(CPP) scanner.cpp

bombard.o: bombard.cpp bombard.h ability.h
	$(CPP) bombard.cpp

main.o: main.cpp
	$(CPP) main.cpp

clean:
	rm ./*.o
