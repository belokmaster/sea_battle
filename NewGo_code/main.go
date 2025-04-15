package main

import (
	"fmt"
	"sea_battle/game"
	"sea_battle/input"
)

func main() {
	var gameField game.Field

	height, width, err := input.GetInput()
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	gameField.Init(height, width)

	fmt.Println("Field:")
	for _, row := range gameField.Arr {
		fmt.Println(row)
	}
}
