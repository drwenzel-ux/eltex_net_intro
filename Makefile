CFLAGS := -g -Wall
CC := gcc
RM := rm

INET_TARGET := tcp_client tcp_server udp_client udp_server
UNIX_TARGET := unix_client unix_server

DEPS := socket.o utils.o
INET_DEPS := inet_socket.o 
UNIX_DEPS := unix_socket.o

.PHONY: clean

SRC_PATH := src/
OBJ_PATH := build/
INC_PATH := -Iinclude

SRC := $(notdir $(wildcard $(SRC_PATH)*.c ))
DEPS := $(addprefix $(OBJ_PATH), $(DEPS))
INET_DEPS := $(addprefix $(OBJ_PATH), $(INET_DEPS))
UNIX_DEPS := $(addprefix $(OBJ_PATH), $(UNIX_DEPS))

all: $(INET_TARGET) $(UNIX_TARGET)

.SECONDEXPANSION:

$(INET_TARGET): $(DEPS) $(INET_DEPS) $(OBJ_PATH)$$@.o
	@echo [INFO] Creating Binary Executable [$@]
	@$(CC) -o $@ $^

$(UNIX_TARGET): $(DEPS) $(UNIX_DEPS) $(OBJ_PATH)$$@.o
	@echo [INFO] Creating Binary Executable [$@]
	@$(CC) -o $@ $^

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)

clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*
	@$(RM) -rfv $(INET_TARGET)
	@$(RM) -rfv $(UNIX_TARGET)
