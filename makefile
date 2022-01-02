CCPP = g++

INC_DIR = -I ~/Tobi/include
INC_DIR += -I ~/Tobi/include/applicationProto
INC_DIR += -I ~/Tobi/include/networkProto
INC_DIR += -I ~/Tobi/include/transportProto
INC_DIR += -I ~/Tobi/include/layers
INC_DIR += -I ~/Tobi/include/dataTypes
INC_DIR += -I ~/Tobi/include/applicationProto/DNS

FILES := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp)

FLAGS := -Wall $(INC_DIR)

tobi:
	$(CCPP) -o bin/tobi $(FILES) $(FLAGS)