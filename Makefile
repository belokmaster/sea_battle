# Указываем компилятор и компиляцию
CXX = g++
CPP = g++ -c

# Директория с исходниками (поскольку Makefile лежит в src, используем эту директорию)
SRC_DIR = .

# Директория для include (json.hpp)
INCLUDE_DIR = $(SRC_DIR)/nlohmann

# Подкаталог с файлами abilities
ABILITIES_DIR = $(SRC_DIR)/abilities

# Главный исходный файл
MAIN_SRC = main.cpp

# Цель по умолчанию (сборка всего проекта)
all: linking clean

# Линковка: объединяем все объектные файлы в один исполнимый файл
linking: $(SRC_DIR)/main.o $(SRC_DIR)/battleField.o $(SRC_DIR)/shipManager.o $(SRC_DIR)/ship.o $(SRC_DIR)/exception.o $(SRC_DIR)/abilityManager.o $(ABILITIES_DIR)/doubleDamage.o $(ABILITIES_DIR)/scanner.o $(ABILITIES_DIR)/bombard.o $(SRC_DIR)/input.o $(SRC_DIR)/output.o $(SRC_DIR)/game.o $(SRC_DIR)/gameState.o $(SRC_DIR)/fileHandler.o
	$(CXX) -o Battleship $^

# Правила для компиляции каждого исходного файла .cpp в объектный файл .o
$(SRC_DIR)/battleField.o: $(SRC_DIR)/battleField.cpp $(SRC_DIR)/shipManager.h $(SRC_DIR)/ship.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/shipManager.o: $(SRC_DIR)/shipManager.cpp $(SRC_DIR)/battleField.h $(SRC_DIR)/ship.h $(SRC_DIR)/exception.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/ship.o: $(SRC_DIR)/ship.cpp $(SRC_DIR)/battleField.h $(SRC_DIR)/shipManager.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/exception.o: $(SRC_DIR)/exception.cpp $(SRC_DIR)/exception.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/abilityManager.o: $(SRC_DIR)/abilityManager.cpp $(SRC_DIR)/abilityManager.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(ABILITIES_DIR)/doubleDamage.o: $(ABILITIES_DIR)/doubleDamage.cpp $(ABILITIES_DIR)/doubleDamage.h $(ABILITIES_DIR)/ability.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(ABILITIES_DIR)/scanner.o: $(ABILITIES_DIR)/scanner.cpp $(ABILITIES_DIR)/scanner.h $(ABILITIES_DIR)/ability.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(ABILITIES_DIR)/bombard.o: $(ABILITIES_DIR)/bombard.cpp $(ABILITIES_DIR)/bombard.h $(ABILITIES_DIR)/ability.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/input.o: $(SRC_DIR)/input.cpp $(SRC_DIR)/input.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/output.o: $(SRC_DIR)/output.cpp $(SRC_DIR)/output.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/game.o: $(SRC_DIR)/game.cpp $(SRC_DIR)/game.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/gameState.o: $(SRC_DIR)/gameState.cpp $(SRC_DIR)/gameState.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/fileHandler.o: $(SRC_DIR)/fileHandler.cpp $(SRC_DIR)/fileHandler.h
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

# Удаление объектных файлов
clean:
	rm -f $(SRC_DIR)/*.o $(ABILITIES_DIR)/*.o
