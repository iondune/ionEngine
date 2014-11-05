SUBDIRS = ionAsset ionBootstrap ionFramework ionGL ionScene ionScience ionWindow

.PHONY: $(addprefix all_, $(SUBDIRS)) $(addprefix clean_, $(SUBDIRS)) all clean remake

all: $(addprefix all_, $(SUBDIRS))

clean: $(addprefix clean_, $(SUBDIRS))

$(addprefix all_, $(SUBDIRS)):
	$(MAKE) -C $(subst all_,, $@) all

$(addprefix clean_, $(SUBDIRS)):
	$(MAKE) -C $(subst clean_,, $@) clean
