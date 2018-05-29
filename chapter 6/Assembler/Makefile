# Compiler to use
CC = clang


# Flags to pass compiler
CFLAGS = -g -I$(HDRDIR) -I$(OBJDIR) -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow # -ansi  # -pedantic
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




# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# dependencies
$(OBJS): $(HDRS) Makefile


# housekeeping
clean:
	$(RM) $(OBJS)


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
