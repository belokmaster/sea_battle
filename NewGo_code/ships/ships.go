package ships

import "fmt"

type Fragment struct {
	HP int
	X  int
	Y  int
}

type Ship struct {
	Horizontal bool
	Length     int
	Fragments  []Fragment
	IsSunk     bool
}

func (s *Ship) InitShip(x, y int, horizontal bool, length int) {
	s.Horizontal = horizontal
	s.Length = length
	s.IsSunk = false
	s.Fragments = make([]Fragment, length)

	for i := 0; i < length; i++ {
		fx, fy := x, y
		if horizontal {
			fx += i
		} else {
			fy += i
		}
		s.Fragments[i] = Fragment{HP: 1, X: fx, Y: fy}
	}
}

func (s *Ship) AttackShip(x, y int) bool {
	for i, frag := range s.Fragments {
		if frag.X == x && frag.Y == y && frag.HP > 0 {
			s.Fragments[i].HP = 0
			fmt.Printf("Корабль по координатам %d %d был атакован.", x, y)
			s.checkIfSunk()
			return true
		}
	}
	return false
}

func (s *Ship) checkIfSunk() {
	for _, frag := range s.Fragments {
		if frag.HP != 0 {
			s.IsSunk = false
			return
		}
	}
	s.IsSunk = true
}
