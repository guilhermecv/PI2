# Projeto Integrador 2 - 2019/1
# Engenharia Eletrônica IFSC
# Guilherme Camargo e Jessica Ribeiro

CC = gcc
CFLAGS = -Wall

# Incluir aqui as bibliotecas utilizadas
LDFLAGS = -l wiringPi

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

EXEC = pi2

all: clean $(EXEC)
	@figlet IFSC - PI2
$(EXEC): $(OBJS)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -c $(CFLAGS) $^

clean:
	@rm -rf *.o $(EXEC)

