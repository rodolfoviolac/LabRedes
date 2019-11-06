# My first makefile
CC = g++
INC_DIR = ./include
SRC_DIR = ./src
BIN_DIR = ./bin
DST_DIR = ./dst

all: client server

client:	$(SRC_DIR)/client.cpp
	$(CC) -o $(DST_DIR)/client $(SRC_DIR)/client.cpp -pthread

server: $(SRC_DIR)/server.cpp
	$(CC) -o $(DST_DIR)/server $(SRC_DIR)/server.cpp -pthread
