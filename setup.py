from setuptools import setup, Extension
import pybind11
import sys

extra_compile_args = []

if sys.platform == "win32":
    extra_compile_args = ["/std:c++17", "/EHsc"]
else:
    extra_compile_args = ["-std=c++17"]

ext_modules = [
    Extension(
        "matrix_py",
        ["matrix_py.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=extra_compile_args,
    ),
]

setup(
    name="matrix_py",
    version="1.0",
    ext_modules=ext_modules,
)