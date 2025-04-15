package input

import (
	"errors"
	"fmt"
)

func checkSize(height, width int) error {
	if height < 5 || width < 5 {
		return errors.New("height and width must be at least 5")
	}
	if height > 15 || width > 15 {
		return errors.New("height and width must be at most 15")
	}
	return nil
}

func GetInput() (int, int, error) {
	var height, width int
	for {
		fmt.Print("Enter height and width: ")
		_, err := fmt.Scan(&height, &width)
		if err != nil {
			fmt.Println("Invalid input. Please enter two integers.")
			var discard string
			fmt.Scanln(&discard)
			continue
		}

		if err := checkSize(height, width); err != nil {
			fmt.Println("Error:", err)
			continue
		}

		return height, width, nil
	}
}
