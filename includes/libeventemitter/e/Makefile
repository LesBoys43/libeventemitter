FILES:=main
.DEFAULT_GOAL=all
.RECIPEPREFIX=~
COMPILE_TARGETS=$(foreach n,$(FILES),$(PWD)/$(n).o)

.PHONY: depend all compile

$(VERBOSE).SILENT:

all: compile depend

depend:
~ @rm -rf .counter || true

compile: $(COMPILE_TARGETS) depend

$(PWD)/%.o: $(PWD)/%.c depend
~ $(word 1,$(ACTORS)) $(CFLAGS) $< -o $@
~ echo LB>>.counter
~ echo "[`cat .counter | wc -l`/$(words $(FILES))] Created C object: $@"
