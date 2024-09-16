# onnxinfo - A tool to show ONNX model summary like torchinfo

This project aims to develop a tool that provides a summary of ONNX models, similar to how torchinfo works for PyTorch models. The tool will focus on offering a layer-wise breakdown, MAC/parameter counts, input/output shapes, and other key model details, all accessible via C++ and Python APIs.

## Basic Information

`onnxinfo` provides a detailed summary of ONNX models, including layer structure and parameter insights, available through both C++ and Python interfaces. 

GitHub URL: https://github.com/ExplorerRay/onnxinfo

## Problem to Solve

With the widespread use of ONNX as an open standard for machine learning models, users used to inspect the structure and parameters of these models by [Netron](https://github.com/lutzroeder/netron). However, it is not that convenient to use it when in a CLI-only environment. This project aims to provide a utility for summarizing ONNX models like torchinfo.

The project applies knowledge from machine learning (deep neural networks) and the ONNX standard, relying on the ONNX Python API for model parsing and analysis.

## Prospective Users

Developers and reasearchers who use ONNX models and need a quick way in python to inspect the model's structure.

## System Architecture

* Input: protocol buffer
  * ONNX format stores a model graph as a protobuf structure (GraphProto)
* Process: Iterate nodes in ONNX and parse info, then calculate
  * ONNX model parsing
    * Parse ONNX models using the ONNX C++ and Python APIs to get info like layer type (e.g., Conv, Gemm, BatchNorm).
  * Layer-wise calculating
    * Input and output shapes
    * Parameter count (e.g., weights and biases)
    * MACs (Multiply-Accumulate Operations)
* Output: Name, Type, Input/Output shapes, MACs, parameters in every layer

## API Description
```python
import onnx
import onnxinfo

onnx_model = onnx.load("<your onnx model path>")

print(onnxinfo.summary(onnx_model))
```

## Engineering Infrastructure
* Build system
  * [GNU make](https://www.gnu.org/software/make/manual/make.html) will be used to manage the C++ build process.
  * Python bindings will be managed using [pybind11](https://github.com/pybind/pybind11) and [setuptools](https://github.com/pypa/setuptools).
* Version control
  * Git (Create branch "dev" and PR)
* Testing framework
  * [GoogleTest](https://github.com/google/googletest) for C++
  * [pytest](https://docs.pytest.org/en/stable/) for Python.
* Documentation
  * [Doxygen](https://www.doxygen.nl/) for C++
  * [Sphinx](https://www.sphinx-doc.org/en/master/) for Python.
  * Markdown
* Continuous integration
  * Use Github CI to run unit tests

## Schedule

The development of `onnxinfo` will follow the schedule below.

* Week 1 (9/30 ~):
  * Survey and implement iterating nodes in ONNX model using C++.
  * Search different kinds of operators in ONNX.
  * Find Pytorch layer corresponding operator in ONNX.
* Week 2-3 (10/7 ~): 
  * Write C++ code to calculate MACs and parameters in nodes. (Conv and Gemm first, others if time is enough)
* Week 4 (10/21 ~): 
  * Make output similar to torchinfo.
  * Write pybind11 code for Python to use.
* Week 5 (10/28 ~):
  * Write unit test for python and C++.
* Week 6 (11/4 ~): 
  * Learn how to use Doxygen and Sphinx, generating documentations.
  * Write usage of this tool.
* Week 7 (11/11 ~): 
  * Learn how to do CI in github, setting up.
* Week 8 (11/18 ~): 
  * Flextime to do any adjustments to this project.

## References
* [Proposal template](https://yyc.solvcon.net/en/latest/nsd/project/project_template.html)
* [torchinfo source code](https://github.com/TylerYep/torchinfo)
* [ONNX github](https://github.com/onnx/onnx)
* [protocol buffer](https://protobuf.dev/overview/)
