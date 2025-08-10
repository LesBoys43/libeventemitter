FILES:=ver
.DEFAULT_GOAL=all
.RECIPEPREFIX=~
COMPILE_TARGETS=$(foreach n,$(FILES),$(PWD)/$(n).o)
LDFLAGS=$(LDFLAGS1)

export ACTORS CFLAGS LDFLAGS1 LDFLAGS2 LDFLAGS

.PHONY: depend all compile subs gem outs outsready

$(VERBOSE).SILENT:

all: gen

gen: depend outs
~ @echo Generated libeventemitter!

outs: compile outsready depend output/libee-ver output/libee.so.1

output/libee-ver: compile
~ $(word 3,$(ACTORS)) $(LDFLAGS2) ver.o -o output/libee-ver
~ @echo Generated binary: $@

output/libee.so.1: compile
~ $(word 2,$(ACTORS)) $(LDFLAGS1) `find | grep '.*\.o' | grep -v 'ver\.o'` -o output/libee.so.1
~ objcopy --localize-symbol=EventEmitter_internals_execEmitting $@ $@
~ objcopy --localize-symbol=EventEmitter_internals_applyBtPolicy $@ $@
~ @echo Generated binary: $@

outsready:
~ mkdir -p output

depend:
~ @rm -rf .counter || true

compile: $(COMPILE_TARGETS) subs depend

$(PWD)/%.o: $(PWD)/%.c depend subs
~ $(word 1,$(ACTORS)) $(CFLAGS) $< -o $@
~ echo LB>>.counter
~ echo "[`cat .counter | wc -l`/$(words $(FILES))] Created C object: $@"

subs: includes_libeventemitter

includes_libeventemitter :
~ cd includes/libeventemitter && $(MAKE)
~ echo Created sub includee: $(PWD)/includes/libeventemitter