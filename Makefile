CC=gcc
CFLAGS=-Wall -fPIC
LIBS=-lpam -lpam_misc
SOURCE=_libpam.c
OBJECT=$(SOURCE:.c=.so)

all: $(OBJECT)

$(OBJECT):
	$(CC) $(SOURCE) -o $@ -shared $(CFLAGS) $(LIBS)
	
clean:
	rm -rf *.o *.so
