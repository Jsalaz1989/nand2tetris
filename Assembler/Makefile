# Compiler to use
CC = clang


# Flags to pass compiler
CFLAGS = -I$(HDRDIR) -I$(OBJDIR) -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow # -ansi  # -pedantic
LDFLAGS =


# Name for executable
EXE = Assembler


# Folders
SRCDIR	= src
OBJDIR	= objs
HDRDIR	= headers

SRCS    := $(shell find $(SRCDIR) -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
HDRS	:= $(shell find $(HDRDIR) -name '*.h')
OBJS    = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
#OBJS = $(SRCS:.c=.o)

# space-separated list of libraries, if any, each of which should be prefixed with -l
LIBS =


# space-separated list of header files
#HDRS = structs.h functions.h parse.h convert.h printFunctions.h converter.h


# if more than one src directory?
#SRCDIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )



# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)



# dependencies
$(OBJS): $(HDRS) Makefile



$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@




# housekeeping
clean:
	$(RM) $(OBJS)
#	rm -f core $(EXE) *.o


distclean: clean
	$(RM) $(APP)

buildrepo:
	@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef