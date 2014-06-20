WORKDIR = ..
BINDIR = $(WORKDIR)/bin
SRCDIR = $(WORKDIR)/src
LIBDIR = $(WORKDIR)/lib

MAKE = make
CC = gcc
CFLAGS = -Wall -pipe -g
LIBS = $(LIBDIR)/libsysadmin.a $(LIBDIR)/libinfoadmin.a
LDFLAGS = -L$(LIBDIR) -lutil -lcrypt -lsysadmin -linfoadmin
INCLUDE = -I$(SRCDIR)/include -I.
AR = ar
ARFLAGS = cr
RM = -rm -f
TARGETS = $(BINDIR)/micposp
OBJS = main.o
SUBDIRS = libutil libcrypt sysadmin infoadmin

all : subdirs $(TARGETS)

subdirs : 
	@for dir in $(SUBDIRS); \
        do $(MAKE) -C $$dir || exit 1; \
        done

$(TARGETS) : $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

clean:
	@for dir in $(SUBDIRS); \
        do $(MAKE) -C $$dir clean || exit 1; \
        done
	$(RM) $(OBJS) $(TARGETS)

.PHONY: all subdirs clean

