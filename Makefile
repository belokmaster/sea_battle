CXX = /usr/bin/g++
CXXFLAGS = -I/opt/homebrew/Cellar/nlohmann-json/3.11.3/include -std=c++17 -c

# Указываем объектные файлы, которые находятся в папке abilities
OBJ = main.o field.o shipManager.o ship.o abilityManager.o abilities/ability.o abilities/bombard.o abilities/doubleDamage.o abilities/scanner.o game.o output.o input.o gameState.o work_with_file.o

# Сборка проекта
all: $(OBJ)
	$(CXX) -o sea_battle $(OBJ)
	rm -f $(OBJ)  # Удаляем объектные файлы после сборки

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f *.o sea_battle abilities/*.o
