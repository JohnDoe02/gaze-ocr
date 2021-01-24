# distutils: language = c++
from libcpp.utility cimport pair

cdef extern from "eyetracker.h":
    cdef cppclass EyeTracker:
        EyeTracker() except +
        pair[float, float] update()
 
cdef extern from "eyetracker.cpp":
    pass

cdef class Tobii4c:
    cdef EyeTracker* c_et

    def __cinit__(self):
        self.c_et = new EyeTracker()

    def __dealloc__(self):
        del self.c_et

    def update(self):
        ret = self.c_et.update()

        return ret.first, ret.second
