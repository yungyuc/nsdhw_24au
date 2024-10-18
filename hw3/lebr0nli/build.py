from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "_matrix",
        sources=["module.cpp", "_matrix.cpp"],
        depends=["_matrix.h"],
        include_dirs=["/usr/include/mkl"],
        extra_compile_args=["-O3", "-march=native", "-ffast-math"],
        extra_link_args=["-lmkl_rt"],
    ),
]

setup(
    name="_vector",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
