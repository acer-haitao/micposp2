WORKDIR = ../..
BINDIR = $(WORKDIR)/bin
SRCDIR = $(WORKDIR)/src
LIBDIR = $(WORKDIR)/lib

MAKE = make
CC = gcc
CFLAGS = -Wall -pipe -g
LIBS = 
LDFLAGS = 
INCLUDE = -I$(SRCDIR)/include -I.
AR = ar
ARFLAGS = cr
RM = -rm -f
TARGETS = $(LIBDIR)/libcrypt.so
OBJS = des.o crypto.o
SUBDIRS = 

all : subdirs $(TARGETS)

subdirs : 
	@for dir in $(SUBDIRS); \
        do $(MAKE) -C $$dir || exit 1; \
        done

$(TARGETS) : $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

clean:
	@for dir in $(SUBDIRS); \
        do $(MAKE) -C $$dir clean || exit 1; \
        done
	$(RM) $(OBJS) $(TARGETS)

.PHONY: all subdirs clean

