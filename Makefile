# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG

# Объектные файлы
OBJ = src/main.o src/bitset/bitset.o src/output/output.o src/handlers/errors.o

# Финальный исполняемый файл
TARGET = bitsetMain

# Компиляция исполняемого файла
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Компиляция каждого .c в .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

# Очистка файлов
cleanf:
	rm -f $(OBJ) $(TARGET)

# Перекомпиляция
rebuild: cleanf $(TARGET)
