### Configuration #########################################

# Build directory
BUILD_DIR		= ../../../new-build/modules

# Include directory
INCLUDE_DIR		= ..

# Default C compiler options.
CFLAGS			= -Wall -I $(INCLUDE_DIR)

# Source files.
SOURCES			= processes.c diskfree.c issue.c time.c

# Corresponding module files.
MODULES			= $(SOURCES:%.c=$(BUILD_DIR)/%.so)

### Rules. ################################################

# Phony targets don't correspond to files that are build;
# they're names for conceptual build targets.
.PHONY:			all clean

# Default target: build everything.
all:			$(MODULES)

# Clean up build products.
clean:
	rm -f $(MODULES)

# Rule for building module shared libraries from the corresponding
# source files. Compile -fPIC and generate a shared object file.
$(MODULES): \
$(BUILD_DIR)/%.so:	%.c $(INCLUDE_DIR)/server.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $<
