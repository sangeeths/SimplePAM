import os
from ctypes import CDLL
from ctypes import c_char_p

# absolute path to _libpam.so 
def _pamlib_abspath():
    _f = os.path.abspath('_libpam.so')
    return _f

# ctypes reference to _pamlib.so
_cdll = CDLL(_pamlib_abspath())

# user readable pam error string
def pam_error_tostr(errcode):
    _cdll._pam_error.restype = c_char_p
    return _cdll._pam_error(errcode)

# invokes pam module to authenticate 
# the given username and password
def validate(un, pw):
    retval = _cdll.validate(un, pw)
    if retval:
        print '%s [%s]' % (pam_error_tostr(retval), un)
        return False
    print '%s successfully authenticated.' % un
    return True

# __END__
