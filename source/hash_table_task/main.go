package main

import (
	"fmt"
	"regexp"
	"strings"

	// hash_table "hash-table-task/hash-table"
	ht "hash-table-task/hash-table"
	"os"
)

/*

1. Сконструировать и реализовать свою хеш таблицу

- изначальный размер 8, коэф-т загрузки 0.75

- Преобразование подаваемого данного в индекс с помощью хеш функции(в ручну) пример: полиномиальный хеш

- Коллизии обрабатываются методом цепочек, каждая корзина таблицы - список в котором хранятся пары значений key-value

- При превышении коэф-та загрузки происходит перехеширование таблицы, размер увеличивается вдвое, все пары заново вставляются в таблицу.

2. Читаем текстовый файл, разбивает на слова, приводим к нижнему регистру, подсчитываем повторения каждого слова: key - слово, value - кол-во повторений

- На вывод 10 самых встречающихся слов, для каждого слова выводим: ind(hash), key, value
- Текст - первая глава, первые три стиха Евгений Онегин

*/

func main() {
	// Чтение всего файла

	const filePath = "../data/onegin.txt"
	// const filePath = "../data/onegin_full.txt"

	data, err := os.ReadFile(filePath)
	text := string(data)
	if err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}
	fmt.Println(text)

	text = strings.ToLower(text)

	// Разбиение на слова (разделители: пробелы и переводы строк)
	re := regexp.MustCompile(`[\p{L}\p{N}-]+`)
	words := re.FindAllString(text, -1)

	fmt.Printf("Найдено слов: %d\n", len(words))
	for i, word := range words {
		fmt.Printf("Слово %d: %s\n", i+1, word)
	}

	hashTable := ht.NewHashTable(8, 0.95)

	for i, word := range words {
		fmt.Printf("%d : %s\n", i, word)
		hashTable.Put(word, 1)
	}

	fmt.Println("\nХеш таблица текста: ")
	hashTable.Print()

	// fmt.Println("Отсортированные ячейки таблицы: ")
	// hashTable.PrintSort()

	fmt.Println("\nСамые часто встречающиеся слова: ")

	hashTable.PrintMostPopularWords(10)
}
