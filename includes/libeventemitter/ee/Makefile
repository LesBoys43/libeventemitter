FILES:=main
.DEFAULT_GOAL=all
.RECIPEPREFIX=~
COMPILE_TARGETS=$(foreach n,$(FILES),$(PWD)/$(n).o)

export ACTORS CFLAGS LDFLAGS

.PHONY: depend all compile subs

$(VERBOSE).SILENT:

all: compile depend

depend:
~ @rm -rf .counter || true

compile: $(COMPILE_TARGETS) subs depend

$(PWD)/%.o: $(PWD)/%.c depend subs
~ $(word 1,$(ACTORS)) $(CFLAGS) $< -o $@
~ echo LB>>.counter
~ echo "[`cat .counter | wc -l`/$(words $(FILES))] Created C object: $@"

subs: actions

actions:
~ cd actions && $(MAKE)
~ echo Created sub includee: $(PWD)/actions