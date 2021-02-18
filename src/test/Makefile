BUILD_DIR = ../../build/testing
BUILD_COMMON = ../../build/common
BUILD_DECODE = ../../build/decode
BUILD_ENCODE = ../../build/encode
BIN_DIR = ../../

test: main.o HuffmanTest.o TimeMeasurer.o $(BUILD_DECODE)/decode.a $(BUILD_ENCODE)/encode.a
	g++ $(BUILD_DIR)/main.o $(BUILD_DIR)/HuffmanTest.o $(BUILD_DIR)/TimeMeasurer.o $(BUILD_DECODE)/decode.a $(BUILD_ENCODE)/encode.a -o $(BIN_DIR)/test
	
main.o: main.cpp
	g++ -c main.cpp -o $(BUILD_DIR)/main.o
	
HuffmanTest.o: HuffmanTest.cpp
	g++ -c HuffmanTest.cpp -o $(BUILD_DIR)/HuffmanTest.o
	
TimeMeasurer.o: TimeMeasurer.cpp
	g++ -c TimeMeasurer.cpp -o $(BUILD_DIR)/TimeMeasurer.o