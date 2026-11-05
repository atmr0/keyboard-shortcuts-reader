# Nome do executável final que será gerado
TARGET = keyb

# Compilador a ser usado
CC = gcc

# Flags de compilação (avisos de erro e otimizações)
CFLAGS = -Wall -Wextra -O2

# Regra padrão executada ao rodar apenas 'make'
all: $(TARGET)

# Como compilar o executável a partir do código fonte
$(TARGET): main.c
	$(CC) $(CFLAGS) main.c keyboard.c -o $(TARGET)

# Regra para limpar os arquivos gerados (make clean)
clean:
	rm -f $(TARGET)
