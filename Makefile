
LIBRARIES = ionAsset ionBootstrap ionFramework ionGL ionScene ionScience ionWindow
TESTS = UnitTests
SUBDIRS = $(LIBRARIES) $(TESTS)

.PHONY: $(addprefix all_, $(SUBDIRS)) $(addprefix clean_, $(SUBDIRS)) $(addprefix remake_, $(SUBDIRS)) $(addprefix depend_, $(SUBDIRS)) all clean remake depend

all: $(addprefix all_, $(SUBDIRS))

clean: $(addprefix clean_, $(SUBDIRS))

remake: $(addprefix remake_, $(SUBDIRS))

depend: $(addprefix depend_, $(SUBDIRS))

$(addprefix all_, $(SUBDIRS)):
	@$(MAKE) -C $(subst all_,, $@) all

$(addprefix clean_, $(SUBDIRS)):
	@$(MAKE) -C $(subst clean_,, $@) clean

$(addprefix remake_, $(SUBDIRS)):
	@$(MAKE) -C $(subst remake_,, $@) remake

$(addprefix depend_, $(SUBDIRS)):
	@$(MAKE) -C $(subst depend_,, $@) depend
