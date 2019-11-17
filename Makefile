SHELL    := /bin/bash
#TOPDIR   := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))/
TOPDIR   := ./
SRCDIR   := $(TOPDIR)src/
OBJDIR   := $(TOPDIR)bin/
OUTDIR   := $(TOPDIR)
NAME     := $(shell cat $(TOPDIR).g++out 2> /dev/null || (read -p "Enter an executable name: " module && echo $$module | tee $(TOPDIR).g++out))
EXE      := $(OUTDIR)$(NAME)


# You should really pass this as a command-line argument, e.g.:
# "make clean all SANITIZE"
# SANITIZER := true

# Everything below this point is generic and could be put into a common
# make include file to be included in other makefiles.

SFILES   := .cc
OFILES   := .o
DFILES   := .d
CC       := g++
CFLAGS   := -std=c++14 -Wall -Werror -g -MMD -Werror=vla -I$(SRCDIR)
LFLAGS   := # -lncurses

SOURCES := $(shell find $(SRCDIR) -type f -name '*'"$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%$(SFILES), $(OBJDIR)%$(OFILES), $(SOURCES))
DEPENDENCIES := $(patsubst $(SRCDIR)%$(SFILES), $(OBJDIR)%$(DFILES), $(SOURCES))

ALLFILES := $(patsubst $(SRCDIR)%$(SFILES), %, $(SOURCES))

ifdef SANITIZER
	CFLAGS := $(CFLAGS) -fsanitize=address,undefined
	LFLAGS := -lasan -lubsan $(LFLAGS)
endif

.PHONY: all debug clean deepclean noop

all: $(EXE)
	@:

noop: ;
	@:

debug: $(SOURCES)
	$(info Compile: $<)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -E -P

$(EXE): $(OBJECTS)
	$(info Link->$@)
	@mkdir -p $(OBJDIR)
	@$(CC) $^ -o $@ $(LFLAGS)

$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES)
	$(info Compile: $<)
	@if cat $< | grep -q -e "TODO"; then \
		echo Warning: TODO item found \($<\). >&2; \
	fi
	@mkdir -p $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(shell dirname $(TOPDIR)$<))
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(DEPENDENCIES) $(EXE)

deepclean: clean
	@rm -f $(TOPDIR).g++out
