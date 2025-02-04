from math import *
import numpy as np

import os

def merge(A, B):
    return np.concatenate((A, B), axis=1)

def minus(A):    
    return -A

def attach(A, B):
    return np.concatenate((A, B), axis = 0)