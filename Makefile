COMMON_DIR = src/common 
ENCODE_DIR = src/encode
DECODE_DIR = src/decode 
TEST_DIR   = src/test

BUILD_DIR = $(PWD)/build
BIN_DIR = $(PWD)

all:
	$(MAKE) common
	$(MAKE) encode
	$(MAKE) decode
	
testing:
	$(MAKE) common
	$(MAKE) encode.a
	$(MAKE) decode.a
	$(MAKE) test
	
common:
	$(MAKE) --directory=$(COMMON_DIR)
	
encode:
	$(MAKE) --directory=$(ENCODE_DIR)
	
encode.a:
	$(MAKE) encode.a --directory=$(ENCODE_DIR)

decode:
	$(MAKE) --directory=$(DECODE_DIR)

decode.a:
	$(MAKE) decode.a --directory=$(DECODE_DIR)

test:
	$(MAKE) --directory=$(TEST_DIR)