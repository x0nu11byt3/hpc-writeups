CXX     := gcc
BUILD   := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/bin
INCLUDE := -I include/ 

OBJECTS_FACTORIAL := $(./src/factorial.c:%.cc=$(OBJ_DIR)/%.o)
OBJECTS_MATRIX_MULTIPLY_PROCCESS := $(./src/matrix_multiplication.c:%.cc=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/factorial $(APP_DIR)/matrix

$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) -lreadline -o $@ -c $<

$(APP_DIR)/factorial: $(OBJECTS_FACTORIAL)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) -lpthread ./src/factorial.c  -o $(APP_DIR)/factorial $(OBJECTS_FACTORIAL)

$(APP_DIR)/matrix: $(OBJECTS_MATRIX_MULTIPLY_PROCCESS)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) ./src/matrix_multiplication.c  -o $(APP_DIR)/matrix $(OBJECTS_MATRIX_MULTIPLY_PROCCESS)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

debug: all

release: all

.PHONY: all build clean debug release
