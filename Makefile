SUBDIRS = ionAsset ionBootstrap ionFramework ionGL ionScene ionScience ionWindow

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
