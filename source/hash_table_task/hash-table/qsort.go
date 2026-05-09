package hash_table

func QSortElementsHT(arr []elementHT, l, r int) []elementHT {
	if l < r {
		s := Partition_Hoa(arr, l, r)
		arr = QSortElementsHT(arr, l, s)
		arr = QSortElementsHT(arr, s+1, r)
	}
	return arr
}

func Partition_Hoa(arr []elementHT, l, r int) int {
	p := arr[(l+r)/2].count
	i := l - 1
	j := r + 1

	for {
		for {
			i++
			if arr[i].count >= p {
				break
			}
		}
		for {
			j--
			if arr[j].count <= p {
				break
			}
		}

		if i >= j {
			return j
		}

		arr[i], arr[j] = arr[j], arr[i]
	}
}
