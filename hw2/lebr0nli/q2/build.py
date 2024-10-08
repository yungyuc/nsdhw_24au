from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "_vector",
        ["src/vector_binding.cc", "src/vector_angle.cc"],
    ),
]

setup(
    name="_vector",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
