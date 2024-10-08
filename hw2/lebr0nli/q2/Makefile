PYTHON = python3
BUILD_DIR = build/
PYTEST_CACHE = .pytest_cache/

all:
	$(PYTHON) build.py build_ext --inplace

test: all
	$(PYTHON) -m pytest -vvv .

clean:
	rm -rf $(BUILD_DIR) $(PYTEST_CACHE) *.so

.PHONY: all test clean
