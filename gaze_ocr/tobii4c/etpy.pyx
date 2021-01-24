# distutils: language = c++
from libcpp.utility cimport pair

cdef extern from "eyetracker.h":
    cdef cppclass EyeTracker:
        EyeTracker() except +
 
cdef extern from "eyetracker.cpp":
    pass

def main():
    cdef EyeTracker et
    et2 = new EyeTracker()
