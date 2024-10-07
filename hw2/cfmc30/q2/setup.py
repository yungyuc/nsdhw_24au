from setuptools import setup, Extension

module = Extension('_vector', sources=['_vector.cpp'])

setup(
    name='_vector',
    version='1.0',
    ext_modules=[module],
)
