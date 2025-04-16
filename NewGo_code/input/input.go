package input

import (
	"errors"
	"fmt"
)

func checkSize(size int) error {
	if size < 5 {
		return errors.New("Size of the field must be at least 5")
	}
	if size > 15 {
		return errors.New("Size of the field must be at most 15")
	}
	return nil
}

func GetInput() (int, error) {
	var size int
	for {
		fmt.Print("Enter size of the field: ")
		_, err := fmt.Scan(&size)
		if err != nil {
			fmt.Println("Invalid input. Please enter two integers.")
			var discard string
			fmt.Scanln(&discard)
			continue
		}

		if err := checkSize(size); err != nil {
			fmt.Println("Error:", err)
			continue
		}

		return size, nil
	}
}
