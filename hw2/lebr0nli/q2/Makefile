PYTHON = python3
BUILD_DIR = build/
PYTEST_CACHE = .pytest_cache/
VENV_DIR = .venv
MODULE = _vector.*.so

all: $(VENV_DIR) $(MODULE)

$(VENV_DIR):
	$(PYTHON) -m venv $(VENV_DIR)
	$(VENV_DIR)/bin/pip install --upgrade pip
	$(VENV_DIR)/bin/pip install pybind11 pytest

$(MODULE): build.py src/vector_angle.cc src/vector_binding.cc
	$(VENV_DIR)/bin/$(PYTHON) build.py build_ext --inplace

test: $(MODULE)
	$(VENV_DIR)/bin/pytest -vvv .

clean:
	rm -rf $(BUILD_DIR) $(PYTEST_CACHE) *.so

clean-all: clean
	rm -rf $(VENV_DIR)

.PHONY: all test clean