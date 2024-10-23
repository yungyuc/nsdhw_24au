from setuptools import setup, Extension

module = Extension('_matrix', sources=['_matrix.cpp'])

setup(
    name='_matrix',
    version='1.0',
    ext_modules=[module],
)
