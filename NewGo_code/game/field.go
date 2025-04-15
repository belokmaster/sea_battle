package game

type Field struct {
	Height int
	Width  int
	Arr    [][]int
}

func (f *Field) Init(height, width int) {
	f.Height = height
	f.Width = width
	for i := 0; i < height; i++ {
		array := make([]int, width)
		f.Arr = append(f.Arr, array)
	}
}
