ADDON = M3U\ Creator
INCLUDE_DIR = ../../../include
LIBRARY_DIR = ../../../lib
RELEASE_DIR = ../../../release/Hare
ADDON_DIR = $(RELEASE_DIR)/add-ons

HDRS =	M3UCreator.h

SRCS =	M3UCreator.cpp

OBJS = $(SRCS:.cpp=.o)

LIBS = -lbe -lroot -laeencoder -ltag
CC = g++
CFLAGS = -DDEBUG -g
LD = g++
LDFLAGS = -nostart -Xlinker -soname="$(ADDON)" -L$(LIBRARY_DIR)
MIMESET = mimeset

$(ADDON) : $(OBJS)
	$(LD) -o $(ADDON) $(OBJS) $(LDFLAGS) $(LIBS)
	$(MIMESET) -f "$(ADDON)"
	chmod 755 $(ADDON)

clean  :
	rm -f *.o $(ADDON)

install : $(ADDON)
	mkdir -p $(ADDON_DIR)
	cp -f $(ADDON) $(ADDON_DIR)/$(ADDON)

cleaninstall : clean
	rm -f $(ADDON_DIR)/$(ADDON)

release : CFLAGS = -O3
release : cleaninstall install
	make clean

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/taglib -o $@
