EXECUTABLE = FlipSideAE
INCLUDE_DIR = ../../../include
LIBRARY_DIR = ../../../lib
RELEASE_DIR = ../../../release/FlipSideAE

HDRS =	Application.h\
			AppView.h\
			AppWindow.h\
			CheckMark.h\
			EditorView.h\
			EncoderListView.h\
			FileNamePatternView.h\
			Settings.h\
			StatusBarFilter.h

SRCS =	Application.cpp\
			AppView.cpp\
			AppWindow.cpp\
			CheckMark.cpp\
			EditorView.cpp\
			EncoderListView.cpp\
			FileNamePatternView.cpp\
			Settings.cpp\
			StatusBarFilter.cpp

OBJS = $(SRCS:.cpp=.o)

RSRCS = FlipsideAE.rsrc

LIBS = -lbe -lroot -lsanta -lstring -laudioinfo -laeencoder -ltag

CC = g++
CFLAGS = -DDEBUG -g
LD = g++
LDFLAGS = -Xlinker -L$(LIBRARY_DIR)
XRES = xres
MIMESET = mimeset

$(EXECUTABLE) : $(OBJS) $(RSRCS)
	$(LD) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS) $(LIBS)
	$(XRES) -o ""$(EXECUTABLE)"" $(RSRCS)
	$(MIMESET) -f "$(EXECUTABLE)"
	chmod 755 $(EXECUTABLE)

clean  :
	rm -f *.o $(EXECUTABLE)

install : $(EXECUTABLE)
	mkdir -p $(RELEASE_DIR)
	cp -f $(EXECUTABLE) $(RELEASE_DIR)/$(EXECUTABLE)

cleaninstall : clean
	rm -f $(RELEASE_DIR)/$(EXECUTABLE)

release : CFLAGS = -O3
release : cleaninstall install
	make clean

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/taglib -o $@
