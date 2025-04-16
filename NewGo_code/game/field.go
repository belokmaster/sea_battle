package game

import (
	"fmt"
	"sea_battle/ships"
)

type Field struct {
	Size  int
	Arr   [][]int
	Ships []ships.Ship
}

func (f *Field) Init(size int) {
	f.Size = size
	for i := 0; i < size; i++ {
		array := make([]int, size)
		f.Arr = append(f.Arr, array)
	}
}

func (f *Field) PutShip(x, y int, ship *ships.Ship) error {
	ship.InitShip(x, y, ship.Horizontal, ship.Length)

	for _, frag := range ship.Fragments {
		if frag.X < 0 || frag.X >= f.Size || frag.Y < 0 || frag.Y >= f.Size {
			return fmt.Errorf("корабль выходит за пределы поля")
		}
		if f.Arr[frag.X][frag.Y] != 0 {
			return fmt.Errorf("я (%d, %d) уже занята", frag.X, frag.Y)
		}
	}

	for _, frag := range ship.Fragments {
		f.Arr[frag.X][frag.Y] = 1
	}

	f.Ships = append(f.Ships, *ship)

	return nil
}

func (f *Field) Attack(x, y int) string {
	if x < 0 || x >= f.Size || y < 0 || y >= f.Size {
		return "miss (out of bounds)"
	}

	if f.Arr[y][x] == -1 || f.Arr[y][x] == 2 {
		return "already targeted"
	}

	for i := range f.Ships {
		if f.Ships[i].AttackShip(x, y) {
			f.Arr[y][x] = 2
			if f.Ships[i].IsSunk {
				return "hit and sunk"
			}
			return "hit"
		}
	}

	f.Arr[y][x] = -1
	return "miss"
}
