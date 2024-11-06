CXX = g++
CPP = g++ -c

all: linking clean

linking: main.o battleField.o shipManager.o ship.o exception.o abilityManager.o abilities/doubleDamage.o abilities/scanner.o abilities/bombard.o
	$(CXX) main.o battleField.o shipManager.o ship.o exception.o abilityManager.o abilities/doubleDamage.o abilities/scanner.o abilities/bombard.o -o Battleship

battleField.o: battleField.cpp shipManager.h ship.h
	$(CPP) battleField.cpp

shipManager.o: shipManager.cpp battleField.h ship.h exception.h
	$(CPP) shipManager.cpp

ship.o: ship.cpp battleField.h shipManager.h
	$(CPP) ship.cpp

exception.o: exception.cpp exception.h
	$(CPP) exception.cpp

abilityManager.o: abilityManager.cpp abilityManager.h abilities/ability.h
	$(CPP) abilityManager.cpp

abilities/doubleDamage.o: abilities/doubleDamage.cpp abilities/doubleDamage.h abilities/ability.h
	$(CPP) abilities/doubleDamage.cpp -o abilities/doubleDamage.o

abilities/scanner.o: abilities/scanner.cpp abilities/scanner.h abilities/ability.h
	$(CPP) abilities/scanner.cpp -o abilities/scanner.o

abilities/bombard.o: abilities/bombard.cpp abilities/bombard.h abilities/ability.h
	$(CPP) abilities/bombard.cpp -o abilities/bombard.o

main.o: main.cpp
	$(CPP) main.cpp

clean:
	rm ./*.o abilities/*.o