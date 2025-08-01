.RECIPEPREFIX = ~
.DEFAULT_GOAL = help
YELPBUILD=yelp-build
YBFLAGS=-o docs/yelp/build
PANDOC=pandoc
PDFLAGS=--quiet --from=mediawiki
INSTALL=install
MANTITLE=LBLang
MANAUTHOR=LesBoys
MKDIR=mkdir -p
INSTFLAGS=-p -m 644
COPY=cp
GZ=gzip
GZFLAGS=-k
DEL=rm -rf
DESTDIR?=/
PREFIX?=$(DESTDIR)/usr/local
MANDB=mandb
SHELL?=bash
WITHYELP?=0
WITHMAN?=1
WITHMD?=1
PGS=config create_and_destroy EventEmitter_controlflags_c EventEmitter_deon_c EventEmitter_emit_c EventEmitter_once_c EventEmitter_on_c EventListener_call_c internals libeventemitter_h
MALLARDFLAGS=$(foreach n,$(PGS),docs/yelp/mallard/$(n).page.flag)
MDS=$(foreach n,$(PGS),docs/markdown/$(n).md)
WTS=$(foreach n,$(PGS),docs/wikitext/$(n).wt)
MANTARGETS=$(foreach n,$(PGS),docs/man/$(n).3)
MANGZTARGETS=$(foreach n,$(MANTARGETS),$(n).gz)

help:
~ @echo 莱斯文档系统
~ @echo 目标：
~ @echo + install: 安装
~ @echo 配置：
~ @echo WITHYELP: 是否安装到 yelp 默认否 依赖 yelp-build
~ @echo WITHMD: 是否安装 markdown 到家 默认是 依赖 pandoc
~ @echo WITHMAN: 是否安装到 man 默认是 依赖 pandoc

install: $(if $(filter $(WITHYELP),1),installyelp,) $(if $(filter $(WITHMD),1),installmd,)  $(if $(filter $(WITHMAN),1),installman,)

installyelp: buildyelp mkyelpdir
~ $(INSTALL) $(INSTFLAGS) docs/yelp/build/* $(PREFIX)/share/help/zh_CN/libee

buildyelp: docs/yelp/build/yelp.js mkyelpdir

mkyelpdir:
~ $(MKDIR) $(PREFIX)/share/help/zh_CN/libee
~ $(MKDIR) docs/yelp/build

docs/yelp/build/yelp.js: $(MALLARDFLAGS) mkyelpdir
~ $(YELPBUILD) html $(YBFLAGS) docs/yelp/mallard/*.page

docs/yelp/mallard/%.page.flag: docs/yelp/mallard/%.page
~ touch $@

installman: archiveman mkmandir
~ $(INSTALL) $(INSTFLAGS) docs/man/*.3.gz $(PREFIX)/share/man/zh_CN/man3

archiveman: buildman $(MANGZTARGETS)

docs/man/%.3.gz: docs/man/%.3 buildman
~ $(GZ) $(GZFLAGS) $<

buildman: $(MANTARGETS) mkmandir

mkmandir:
~ $(MKDIR) $(PREFIX)/share/man/zh_CN/man3
~ $(MKDIR) docs/man

docs/man/%.3: docs/wikitext/%.wt mkmandir
~ $(PANDOC) $(PDFLAGS) -t man -o $@ $<

installmd: buildmd mkmddir
~ $(INSTALL) $(INSTFLAGS) docs/markdown/* $(HOME)/libee-docs

buildmd: $(MDS) mkmddir

mkmddir:
~ $(MKDIR) $(HOME)/libee-docs
~ $(MKDIR) docs/markdown

docs/markdown/%.md: docs/wikitext/%.wt mkmddir
~ $(PANDOC) $(PDFLAGS) -t markdown -o $@ $<