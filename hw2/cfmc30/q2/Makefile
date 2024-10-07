BUILD_DIR = build
SO_FILES := $(wildcard *.so)

.PHONY: all
all: SO_FILES
SO_FILES: $(BUILD_DIR)/Makefile
	@echo "Building CMake project..."
	@cmake --build $(BUILD_DIR)
	cp $(BUILD_DIR)/*.so ./

$(BUILD_DIR)/Makefile: 
	@echo "Running CMake configuration..."
	@cmake -S . -B $(BUILD_DIR)

test: SO_FILES test_vector_math.py
	@echo "Running pytest..."
	pytest

.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@rm -rf __pycache__ *.so
