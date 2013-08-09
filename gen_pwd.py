import random
import crypt

_s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"
_salt_len = 16

pwd = raw_input("Enter password: ")

salt = ', '.join(random.sample(set(_s), _salt_len)).replace(', ', '')
salt = '$6$%s$' % salt
crypt_pwd = crypt.crypt(pwd, salt)

print "pwd = %s" % crypt_pwd


