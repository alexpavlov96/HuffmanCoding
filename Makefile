BUILD_DIR = ${CURDIR}/build
BIN_DIR = ${CURDIR}

COMMON_SRC = ${CURDIR}/src/common
ENCODE_SRC = ${CURDIR}/src/encode
DECODE_SRC = ${CURDIR}/src/decode
TEST_SRC =   ${CURDIR}/src/test

all: 
	$(MAKE) $(BIN_DIR)/encode
	$(MAKE) $(BIN_DIR)/decode
	
#common 

$(BUILD_DIR)/HuffmanHeader.o: $(COMMON_SRC)/HuffmanHeader.cpp
	g++ -c $(COMMON_SRC)/HuffmanHeader.cpp -o $(BUILD_DIR)/HuffmanHeader.o	

#encode
	
$(BIN_DIR)/encode: $(BUILD_DIR)/main_enc.o $(BUILD_DIR)/encode.a
	g++ $(BUILD_DIR)/main_enc.o $(BUILD_DIR)/encode.a -o $(BIN_DIR)/encode

$(BUILD_DIR)/encode.a: $(BUILD_DIR)/Encoder.o $(BUILD_DIR)/EncoderHelper.o $(BUILD_DIR)/FrequencyNode.o $(BUILD_DIR)/HuffmanHeader.o
	ar ru $(BUILD_DIR)/encode.a $(BUILD_DIR)/Encoder.o $(BUILD_DIR)/EncoderHelper.o $(BUILD_DIR)/FrequencyNode.o $(BUILD_DIR)/HuffmanHeader.o
	ranlib $(BUILD_DIR)/encode.a
	
$(BUILD_DIR)/main_enc.o: $(ENCODE_SRC)/main.cpp
	g++ -c $(ENCODE_SRC)/main.cpp -o $(BUILD_DIR)/main_enc.o
	
$(BUILD_DIR)/Encoder.o: $(ENCODE_SRC)/Encoder.cpp
	g++ -c $(ENCODE_SRC)/Encoder.cpp -o $(BUILD_DIR)/Encoder.o
	
$(BUILD_DIR)/EncoderHelper.o: $(ENCODE_SRC)/EncoderHelper.cpp
	g++ -c $(ENCODE_SRC)/EncoderHelper.cpp -o $(BUILD_DIR)/EncoderHelper.o

$(BUILD_DIR)/FrequencyNode.o: $(ENCODE_SRC)/FrequencyNode.cpp
	g++ -c $(ENCODE_SRC)/FrequencyNode.cpp -o $(BUILD_DIR)/FrequencyNode.o

# decode

$(BIN_DIR)/decode: $(BUILD_DIR)/main_dec.o $(BUILD_DIR)/decode.a
	g++ $(BUILD_DIR)/main_dec.o $(BUILD_DIR)/decode.a -o $(BIN_DIR)/decode

$(BUILD_DIR)/decode.a: $(BUILD_DIR)/Decoder.o $(BUILD_DIR)/DecoderHelper.o $(BUILD_DIR)/HuffmanHeader.o
	ar ru $(BUILD_DIR)/decode.a $(BUILD_DIR)/Decoder.o $(BUILD_DIR)/DecoderHelper.o $(BUILD_DIR)/HuffmanHeader.o
	ranlib $(BUILD_DIR)/decode.a
	
$(BUILD_DIR)/Decoder.o: $(DECODE_SRC)/Decoder.cpp
	g++ -c $(DECODE_SRC)/Decoder.cpp -o $(BUILD_DIR)/Decoder.o
	
$(BUILD_DIR)/DecoderHelper.o: $(DECODE_SRC)/DecoderHelper.cpp
	g++ -c $(DECODE_SRC)/DecoderHelper.cpp -o $(BUILD_DIR)/DecoderHelper.o

$(BUILD_DIR)/main_dec.o: $(DECODE_SRC)/main.cpp
	g++ -c $(DECODE_SRC)/main.cpp -o $(BUILD_DIR)/main_dec.o

# test

test: $(BUILD_DIR)/main_test.o $(BUILD_DIR)/HuffmanTest.o $(BUILD_DIR)/TimeMeasurer.o $(BUILD_DIR)/decode.a $(BUILD_DIR)/encode.a
	g++ $(BUILD_DIR)/main_test.o $(BUILD_DIR)/HuffmanTest.o $(BUILD_DIR)/TimeMeasurer.o $(BUILD_DIR)/decode.a $(BUILD_DIR)/encode.a -o $(BIN_DIR)/test
	
$(BUILD_DIR)/main_test.o: $(TEST_SRC)/main.cpp
	g++ -c $(TEST_SRC)/main.cpp -o $(BUILD_DIR)/main_test.o
	
$(BUILD_DIR)/HuffmanTest.o: $(TEST_SRC)/HuffmanTest.cpp
	g++ -c $(TEST_SRC)/HuffmanTest.cpp -o $(BUILD_DIR)/HuffmanTest.o
	
$(BUILD_DIR)/TimeMeasurer.o: $(TEST_SRC)/TimeMeasurer.cpp
	g++ -c $(TEST_SRC)/TimeMeasurer.cpp -o $(BUILD_DIR)/TimeMeasurer.o