# Primary compiler
CC := g++

SRCDIR := src
INCLUDEDIR = include
TESTDIR = test
BUILDDIR := build
TARGETDIR := bin

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name \*.$(SRCEXT) ! -name main.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TARGET := $(TARGETDIR)/main
TESTER := $(TARGETDIR)/tester
CFLAGS := -g -Wall
LIB :=
INC := -I $(INCLUDEDIR)

all: $(TARGET)

$(TARGET): dirs $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $(SRCDIR)/main.$(SRCEXT) $(filter-out dirs, $^)

dirs:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)

$(BUILDDIR)/%.o: dirs $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $(word 2, $^)

clean:
	rm -rvf $(BUILDDIR) $(TARGETDIR)/*;

tester: $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $(TESTER) $(TESTDIR)/tester.$(SRCEXT) $^;

.PHONY: all clean
