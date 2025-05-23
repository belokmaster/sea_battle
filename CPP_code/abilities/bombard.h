#ifndef BOMBARD_H
#define BOMBARD_H

#include "ability.h"
#include "../shipManager.h"
#include "../field.h"
#include "../output.h"  // Включаем необходимый заголовочный файл для Output

class Bombard : public Ability {
private:
    Field* field;          // Указатель на поле
    shipManager* managerfield; // Указатель на менеджер
    Output output;         // Объект Output для вывода сообщений

public:
    // Конструктор класса Bombard, принимает указатели на shipManager и Field
    Bombard(shipManager* managerfield, Field* field);
    
    // Метод использования способности
    void useAbility() override;  // Переопределяем метод из iAbility
    
    // Деструктор по умолчанию
    virtual ~Bombard() = default;

private:
    // Вспомогательные методы для получения случайного индекса корабля и сегмента
    int getRandomShipIndex() const;
    int getRandomSegmentIndex(int shipIndex) const;
};

#endif
