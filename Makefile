CC = gcc
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -DDEBUG -g
LDFLAGS =
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = test

# Source and object files
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TESTS := $(wildcard $(TESTDIR)/*.c)

# Default target
all: $(BINDIR)/app

# Debug target
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(BINDIR)/app

# Compile the application
$(BINDIR)/app: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests (assuming test files are in TESTDIR and are standalone programs)
test: $(TESTS)
	@for test in $^ ; do \
		echo "Running $$test..."; \
		$(CC) $(CFLAGS) $$test -o $(OBJDIR)/$$(basename $$test .c) && $(OBJDIR)/$$(basename $$test .c); \
	done

# Clean up
clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

.PHONY: all debug test clean
