BLOCKLISTS_DIR = @BLOCKLISTS_DIR@
LOCAL_BLOCKLIST_DIR = @LOCAL_BLOCKLIST_DIR@
MASTER_BLOCKLIST_DIR = @MASTER_BLOCKLIST_DIR@

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	docs \
	pglcmd \
	pgld \
	$(QT_SUB)

# All other docs are added automatically distributed by automake:
dist_doc_DATA = \
	BUGS \
	README.blocklists \
	README.dbus \
	README.pglgui

EXTRA_DIST = \
	autogen.sh \
	debian/changelog \
	debian/compat \
	debian/control \
	debian/copyright \
	debian/moblock.config \
	debian/moblock.templates \
	debian/pglcmd.config \
	debian/pglcmd.dirs \
	debian/pglcmd.examples \
	debian/pglcmd.install \
	debian/pglcmd.links \
	debian/pglcmd.postinst.in \
	debian/pglcmd.postrm \
	debian/pglcmd.preinst \
	debian/pglcmd.templates \
	debian/pgld.dirs \
	debian/pgld.docs \
	debian/pgld.install \
	debian/pgld.manpages \
	debian/pglgui.docs \
	debian/pglgui.install \
	debian/pglgui.links \
	debian/pglgui.postinst \
	debian/po/POTFILES.in \
	debian/po/templates.pot \
	debian/README.Debian \
	debian/rules \
	debian/source/format \
	debian/watch

install-data-local:
	@$(INSTALL) -d $(DESTDIR)$(MASTER_BLOCKLIST_DIR)
	@$(INSTALL) -d $(DESTDIR)$(BLOCKLISTS_DIR)
	@$(INSTALL) -d $(DESTDIR)$(LOCAL_BLOCKLIST_DIR)
	@$(INSTALL) -d $(DESTDIR)$(PIDDIR)
	@$(INSTALL) -d $(DESTDIR)$(LOGDIR)
	@$(INSTALL) -d $(DESTDIR)$(TMPDIR)

CLEANFILES = \
	autom4te.cache/*
