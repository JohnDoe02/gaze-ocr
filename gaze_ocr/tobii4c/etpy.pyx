# distutils: language = c++
from libcpp.utility cimport pair
import threading
import time
import copy

cdef extern from "eyetracker.h":
    cdef cppclass EyeTracker:
        EyeTracker() except +
        pair[float, float] update()
 
cdef extern from "eyetracker.cpp":
    pass

cdef class Tobii4c:
    cdef EyeTracker* c_et
    cdef _gazeX
    cdef _gazeY
    cdef _threaded_update
    cdef _exit_flag
    cdef _lock

    def __init__(self):
        self._gazeX = 0.0
        self._gazeY = 0.0

        self._exit_flag = threading.Event()
        self._lock = threading.Lock()
        self._threaded_update = threading.Thread(target=self.__update, args=())
        self._threaded_update.start()

    def __cinit__(self):
        self.c_et = new EyeTracker()

    def __dealloc__(self):
        self._exit_flag.set()
        self._threaded_update.join()

        del self.c_et

    def __update(self):
        # The tobii4c supports a refresh rate of up to 90Hz
        interval = 1.0/90

        # Will run until _exit_flag.set() is called
        while not self._exit_flag.wait(timeout=interval):
            ret = self.c_et.update()

            with self._lock:
                self._gazeX = ret.first
                self._gazeY = ret.second

    def getGaze(self):
        with self._lock:
            gazeX = copy.deepcopy(self._gazeX)
            gazeY = copy.deepcopy(self._gazeY)

        return gazeX, gazeY
