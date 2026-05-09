package hash_table

import (
	"bufio"
	"fmt"
	"os"
)

// HashTable - хеш-таблица с цепочками
type HashTable struct {
	buckets    []*bucket
	size       int
	capacity   int
	loadFactor float64
}

type bucket struct {
	head *elementHT
}

type elementHT struct {
	word  string
	count int
	next  *elementHT
}

// NewHashTable - создает новую хеш-таблицу
func NewHashTable(capacity int, loadFactor float64) *HashTable {

	buckets := make([]*bucket, capacity)

	for i := 0; i < capacity; i++ {
		buckets[i] = &bucket{}
	}

	return &HashTable{
		buckets:    buckets,
		size:       0,
		capacity:   capacity,
		loadFactor: loadFactor,
	}
}

// func (h HashTable) getIndex(word string) int {
// 	return GetHashString(word) % h.size
// }

// func (h HashTable) Add(word string) {

// }

func (ht *HashTable) GetIndex(word string) int {
	hash := GetHashString(word)
	return hash % ht.capacity
}

func (ht *HashTable) getIndex(hash int) int {
	return hash % ht.capacity
}

func (h *HashTable) Put(word string, change int) {

	if h.size >= int(float64(h.capacity)*h.loadFactor) {
		h.resize()
	}

	ind := h.getIndex(GetHashString(word))

	buck := h.buckets[ind]

	current := buck.head

	for current != nil {
		if current.word == word {
			current.count += change
			return
		}

		current = current.next
	}

	newHead := &elementHT{
		word:  word,
		count: change,
		next:  buck.head,
	}

	buck.head = newHead
	h.size++
}

func (h *HashTable) Get(word string) (count int, status bool) {
	ind := h.getIndex(GetHashString(word))

	buck := h.buckets[ind]

	current := buck.head

	for current != nil {
		if current.word == word {
			return current.count, true
		}

		current = current.next
	}

	return -1, false
}

func pressEnterToContinue() {
	fmt.Print("Нажмите Enter для продолжения...")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
}

// resize - увеличивает размер таблицы
func (ht *HashTable) resize() {

	// fmt.Printf("Resize table!\n elements: %d(%.3f%%)\n old capacity: %d\n new capacity: %d\n", ht.size, float64(ht.size)/float64(ht.capacity), ht.capacity, 2*ht.capacity)

	// ht.Print()

	// pressEnterToContinue()

	newCapacity := ht.capacity * 2
	newHT := NewHashTable(newCapacity, ht.loadFactor)

	for _, b := range ht.buckets {
		current := b.head
		for current != nil {
			newHT.Put(current.word, current.count)
			current = current.next
		}
	}

	ht.buckets = newHT.buckets
	ht.capacity = newCapacity
}

func (ht *HashTable) remove(word string) bool {
	ind := ht.getIndex(GetHashString(word))

	buck := ht.buckets[ind]

	if buck.head == nil {
		return false
	}

	if buck.head.word == word {
		buck.head = buck.head.next
		ht.size--
		return true
	}

	prev := buck.head
	current := buck.head.next

	for current != nil {
		if current.word == word {
			prev.next = current.next
			ht.size--
			return true
		}
		prev = current
		current = current.next
	}

	return false
}

func (ht *HashTable) Contains(word string) bool {
	_, ok := ht.Get(word)
	return ok
}

func (elem *elementHT) ToString() string {
	if elem == nil {
		return "nil"
	}

	return fmt.Sprintf("Слово: \"%s\" Повторений: %d", elem.word, elem.count)
}

func (ht *HashTable) Print() {
	for ind := 0; ind < ht.capacity; ind++ {
		buck := ht.buckets[ind]
		current := buck.head

		bucketsStr := ""

		for current != nil {
			bucketsStr += " --> " + current.ToString()
			current = current.next
		}
		fmt.Printf("[%d]: %s\n", ind, bucketsStr)
	}
}

func (ht *HashTable) PrintSort() {
	// fmt.Printf("Size: %d, Capacity: %d\n", ht.size, ht.capacity)
	data := make([]elementHT, 0, ht.size)

	for ind := 0; ind < ht.capacity; ind++ {
		buck := ht.buckets[ind]
		current := buck.head

		for current != nil {
			if current.count != 0 {
				data = append(data, elementHT{
					word:  current.word,
					count: current.count,
				})
			}
			// fmt.Println(current.word, current.count)
			current = current.next
		}
	}

	data = QSortElementsHT(data, 0, len(data)-1)

	for i, el := range data {
		fmt.Printf("[%d]: \"%s\", %d\n", i, el.word, el.count)
	}

}

func (ht *HashTable) PrintMostPopularWords(count int) {
	// fmt.Printf("Size: %d, Capacity: %d\n", ht.size, ht.capacity)
	data := make([]elementHT, 0, ht.size)

	for ind := 0; ind < ht.capacity; ind++ {
		buck := ht.buckets[ind]
		current := buck.head

		for current != nil {
			if current.count != 0 {
				data = append(data, elementHT{
					word:  current.word,
					count: current.count,
				})
			}
			// fmt.Println(current.word, current.count)
			current = current.next
		}
	}

	data = QSortElementsHT(data, 0, len(data)-1)

	for i := 0; i < count; i++ {
		fmt.Printf("[%d]: %3d : %s\n", i, ht.GetIndex(data[len(data)-i-1].word), data[len(data)-i-1].ToString())
	}
}
