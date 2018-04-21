## Process this file with automake to produce Makefile.in

EXTRA_DIST  = CombPolDBLVD1.h  \
              CombPolDBLVD2.h  \
              CombPolVD1VD2.h  \
              CombRotDBLVD1.h  \
              CombRotDBLVD2.h  \
              CombRotVD1VD2.h  \
              CombScalDBLVD1.h \
              CombScalDBLVD2.h \
              CombScalVD1VD2.h \
              CombVecDBLVD1.h  \
              CombVecDBLVD2.h  \
              CombVecVD1VD2.h  \
              ConvDBLVD1.h     \
              ConvDBLVD2.h     \
              ConvVD1VD2.h

install-data-local : $(EXTRA_DIST)
	$(mkinstalldirs) $(DESTDIR)$(pkgincludedir)/conversions
	@list='$(EXTRA_DIST)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(pkgincludedir)/conversions/$$p"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(pkgincludedir)/conversions/$$p; \
	done

uninstall-local:
	rm -fr $(DESTDIR)$(pkgincludedir)/conversions
