package hash_table

func GetHashString(str string) int {
	hash := 0

	for _, ch := range str {
		hash = (hash << 5) - hash + int(ch)
	}

	if hash < 0 {
		hash = -hash
	}

	return hash
}
