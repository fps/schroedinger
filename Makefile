COMPILE_FLAGS = -Wall `pkg-config jack alsa sndfile --cflags`
#COMPILE_FLAGS += -g -O2 
COMPILE_FLAGS += -O0 -funroll-loops  -m3dnow -mmmx -ffast-math -g -pg

LINK_FLAGS    = `pkg-config jack alsa sndfile --libs` -lm -g -pg


TARGET = schroedinger 
PREFIX = /usr/local

STUFF = field main global schroedinger
OBJECTS = $(STUFF:%=%.o)
SOURCES = $(STUFF:%=%.cc)
HEADERS = $(STUFF:%=%.h)

all: $(TARGET) txt2wav

txt2wav: txt2wav.cc
	g++ -o txt2wav txt2wav.cc $(COMPILE_FLAGS) $(LINK_FLAGS)


$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LINK_FLAGS)

$(OBJECTS): %.o: %.cc  $(HEADERS) Makefile
	$(CXX) -c $< $(COMPILE_FLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET) *~ *.o  core* fps txt2wav

.PHONY: install
install: $(TARGET)
	cp $(TARGET) $(PREFIX)/bin/
