.DEFAULT_GOAL=all
.RECIPEPREFIX=~
COMPILE_TARGETS=$(foreach n,$(FILES),$(PWD)/$(n).o)

export ACTORS CFLAGS LDFLAGS

.PHONY: all compile subs ee el e

$(VERBOSE).SILENT:

all: compile

compile: subs

subs: ee el e

ee:
~ cd ee && $(MAKE)
~ echo Created sub includee: $(PWD)/ee

el:
~ cd el && $(MAKE)
~ echo Created sub includee: $(PWD)/el

e:
~ cd e && $(MAKE)
~ echo Created sub includee: $(PWD)/e

