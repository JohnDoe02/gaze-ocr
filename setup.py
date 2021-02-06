import setuptools
from distutils.extension import Extension

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="gaze-ocr",
    version="0.1.0",
    author="James Stout",
    author_email="james.wolf.stout@gmail.com",
    description="Library for applying OCR to where the user is looking.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/wolfmanstout/gaze-ocr",
    packages=["gaze_ocr"],
    setup_requires=[
        # Setuptools 18.0 properly handles Cython extensions.
        'setuptools>=18.0',
        'cython',
    ],
    install_requires=[
        "screen-ocr",
        "dragonfly2",
        'futures; python_version < "3.2"',
    ],
    classifiers=[
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: OS Independent",
    ],
    ext_modules = [
        Extension("etpy", 
                  sources=["gaze_ocr/tobii4c/etpy.pyx"],
                  language="c++",
                  library_dirs=["/usr/lib/tobii/"],
                  libraries=["tobii_stream_engine"],
                  extra_compile_args=["-std=c++17"])
        ]
)
