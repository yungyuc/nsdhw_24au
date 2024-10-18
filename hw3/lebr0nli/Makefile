PYTHON := python3
VENV_DIR := .venv
VENV_PYTHON := $(VENV_DIR)/bin/python
VENV_PIP := $(VENV_DIR)/bin/pip

BUILD_DIR := build
PYTEST_CACHE := .pytest_cache
MODULE := _matrix.*.so
PYCACHE := __pycache__

BUILD_SCRIPT := build.py

SOURCES := _matrix.cpp _matrix.h module.cpp

.PHONY: all venv test clean clean-all

all: $(MODULE)

venv: $(VENV_DIR)

$(VENV_DIR):
	$(PYTHON) -m venv $(VENV_DIR)
	$(VENV_PIP) install --upgrade pip
	$(VENV_PIP) install pybind11 pytest

$(MODULE): venv $(BUILD_SCRIPT) $(SOURCES)
	$(VENV_PYTHON) $(BUILD_SCRIPT) build_ext --inplace

test: $(MODULE)
	$(VENV_PYTHON) -m pytest -vvv .

clean:
	rm -rf $(BUILD_DIR) $(PYTEST_CACHE) $(MODULE) $(PYCACHE)

clean-all: clean
	rm -rf $(VENV_DIR)
