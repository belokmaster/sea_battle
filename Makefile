CXX = /usr/bin/g++
CXXFLAGS = -I/opt/homebrew/Cellar/nlohmann-json/3.11.3/include -std=c++17 -c

# Указываем объектные файлы, которые находятся в папке abilities
OBJ = main.o field.o manager.o ship.o ability_manager.o abilities/ability.o abilities/bombard.o abilities/doubleDamage.o abilities/scanner.o gamesession.o output.o input.o game_state.o work_with_file.o

# Сборка проекта
all: $(OBJ)
	$(CXX) -o all $(OBJ)

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f *.o all abilities/*.o
