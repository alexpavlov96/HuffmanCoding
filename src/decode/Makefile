BUILD_DIR = ../../build/decode
BUILD_COMMON = ../../build/common
BIN_DIR = ../../

decode: main.o decode.a
	g++ $(BUILD_DIR)/main.o $(BUILD_DIR)/decode.a -o $(BIN_DIR)/decode

decode.a: Decoder.o DecoderHelper.o $(BUILD_COMMON)/HuffmanHeader.o
	ar ru $(BUILD_DIR)/decode.a $(BUILD_DIR)/Decoder.o $(BUILD_DIR)/DecoderHelper.o $(BUILD_COMMON)/HuffmanHeader.o
	ranlib $(BUILD_DIR)/decode.a
	
Decoder.o: Decoder.cpp
	g++ -c Decoder.cpp -o $(BUILD_DIR)/Decoder.o
	
DecoderHelper.o: DecoderHelper.cpp
	g++ -c DecoderHelper.cpp -o $(BUILD_DIR)/DecoderHelper.o

main.o: main.cpp
	g++ -c main.cpp -o $(BUILD_DIR)/main.o