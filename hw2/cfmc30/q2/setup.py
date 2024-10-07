from setuptools import setup, Extension

module = Extension('fdct', sources=['fdct.cpp'])

setup(
    name='fdct',
    version='1.0',
    ext_modules=[module],
)
