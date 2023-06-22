CXX     := gcc
BUILD   := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/bin
INCLUDE := -I include/ 

OBJECTS_FACTORIAL := $(./src/factorial.c:%.cc=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/factorial

$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) -lreadline -o $@ -c $<

$(APP_DIR)/factorial: $(OBJECTS_FACTORIAL)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) -lpthread ./src/factorial.c  -o $(APP_DIR)/factorial $(OBJECTS_FACTORIAL)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

debug: all

release: all

.PHONY: all build clean debug release
