CFLAGS := -g -Wall
CC := gcc
RM := rm
TARGET := tcp_client tcp_server udp_client udp_server unix_server unix_client
DEPS := socket.o unix_socket.o inet_socket.o utils.o

.PHONY: $(TARGET) clean

SRC_PATH := src/
OBJ_PATH := build/
INC_PATH := -Iinclude

SRC := $(notdir $(wildcard $(SRC_PATH)*.c ))
OBJ := $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC))
DEPS := $(addprefix $(OBJ_PATH), $(DEPS))

all: $(OBJ) $(TARGET)

$(TARGET): $(DEPS)
	@echo [INFO] Creating Binary Executable [$@]
	@$(CC) -o $@  $(OBJ_PATH)$@.o $^

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH) 

clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*
	@$(RM) -rfv $(TARGET)
