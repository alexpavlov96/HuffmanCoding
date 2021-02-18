BUILD_DIR = ../../build/encode
BUILD_COMMON = ../../build/common
BIN_DIR = ../../

encode: main.o encode.a
	g++ $(BUILD_DIR)/main.o $(BUILD_DIR)/encode.a -o $(BIN_DIR)/encode

encode.a: Encoder.o EncoderHelper.o FrequencyNode.o $(BUILD_COMMON)/HuffmanHeader.o
	ar ru $(BUILD_DIR)/encode.a $(BUILD_DIR)/Encoder.o $(BUILD_DIR)/EncoderHelper.o $(BUILD_DIR)/FrequencyNode.o $(BUILD_COMMON)/HuffmanHeader.o
	ranlib $(BUILD_DIR)/encode.a
	
main.o: main.cpp
	g++ -c main.cpp -o $(BUILD_DIR)/main.o
	
Encoder.o: Encoder.cpp
	g++ -c Encoder.cpp -o $(BUILD_DIR)/Encoder.o
	
EncoderHelper.o: EncoderHelper.cpp
	g++ -c EncoderHelper.cpp -o $(BUILD_DIR)/EncoderHelper.o

FrequencyNode.o: FrequencyNode.cpp
	g++ -c FrequencyNode.cpp -o $(BUILD_DIR)/FrequencyNode.o