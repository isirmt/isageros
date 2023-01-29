SUFFIX := .cpp
PROGNAME := isageros
COMPILER := g++
CPPFLAGS := -std=c++11 -O2
LIBFLAGS := -lglut -lGLU -lGL -lm

SOURCEDIR := ./src/
INCLUDEDIR := -I./inc/ -I./lib/
OUTDIR := ./build/
ASSETSDIR := ./assets/

TARGET := $(OUTDIR)$(PROGNAME)
SOURCES := $(wildcard $(SOURCEDIR)*$(SUFFIX))
OBJECTS := $(addprefix $(OUTDIR),$(notdir $(SOURCES:$(SUFFIX)=.o)))

all: $(OBJECTS) $(LIBFLAGS)
	$(COMPILER) $(INCLUDEDIR) -o $(TARGET) $^

%.o:  $(addprefix $(SOURCEDIR),$(notdir $(%:.o=$(SUFFIX))))
	$(COMPILER) $(INCLUDEDIR) $(LIBFLAGS) $(CPPFLAGS) -o $@ -c $(SOURCEDIR)$(basename $(notdir $@))$(SUFFIX)

.PHONY: clean

clean:
	$(RM) $(OUTDIR)*.o $(OUTDIR)$(PROGNAME) $(PROGNAME)

run:
	$(OUTDIR)$(PROGNAME)