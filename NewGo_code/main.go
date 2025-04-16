package main

import (
	"fmt"
	"sea_battle/game"
	"sea_battle/input"
	"sea_battle/ships"
)

func main() {
	var gameField game.Field

	size, err := input.GetInput()
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	gameField.Init(size)

	ship := ships.Ship{Horizontal: true, Length: 3}
	err = gameField.PutShip(2, 3, &ship)
	if err != nil {
		fmt.Println("Ошибка размещения корабля:", err)
	}

	fmt.Println("Поле:")
	for _, row := range gameField.Arr {
		fmt.Println(row)
	}

	result := gameField.Attack(3, 3)
	result2 := gameField.Attack(3, 3)
	result3 := gameField.Attack(4, 3)
	result4 := gameField.Attack(5, 3)
	fmt.Println(result, result2, result3, result4)
}
