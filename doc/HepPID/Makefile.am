## Process this file with automake to produce Makefile.in

# EXTRA_DIST are already built - this is just used to install them

if USE_GMAKE
  MAKE = gmake
endif

doc_installdir = $(prefix)/doc/HepPID

HEPPID_DOC = HepPID.pdf montecarlorpp.pdf

EXTRA_DIST = $(HEPPID_DOC)

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	for file in $(HEPPID_DOC); do \
	  if test -f $(srcdir)/$$file; then \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(doc_installdir)/$$file; \
	  fi; done

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = *.aux *.log *.toc *.dvi

