CXX = /usr/bin/g++
CXXFLAGS = -I/opt/homebrew/Cellar/nlohmann-json/3.11.3/include -std=c++17 -c
OBJ = main.o field.o manager.o ship.o ability_manager.o i_ability.o bombardment.o double_damage.o scanner.o gamesession.o output.o input.o game_state.o work_with_file.o

all: $(OBJ)
	$(CXX) -o all $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o all
