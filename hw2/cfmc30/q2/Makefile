BUILD_DIR = build

.PHONY: all
all: $(BUILD_DIR)/Makefile
	@echo "Building CMake project..."
	@cmake --build $(BUILD_DIR)

$(BUILD_DIR)/Makefile: 
	@echo "Running CMake configuration..."
	@cmake -S . -B $(BUILD_DIR)

.PHONY: test
test:
	@echo "Running pytest..."
	pytest

.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@rm -rf __pycache__
