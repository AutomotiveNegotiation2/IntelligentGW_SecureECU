bindir ?= /usr/bin/
confdir ?= /etc/
servicedir ?= /etc/systemd/system/
define allow-override
  $(if $(or $(findstring environment,$(origin $(1))),\
            $(findstring command line,$(origin $(1)))),,\
    $(eval $(1) = $(2)))
endef
$(call allow-override,CC,$(CROSS_COMPILE)gcc)
LDFLAGS += -pthread

SCRIPTS := tapif.sh cleantapif.sh
EXECS := tapif
CONFIGS := J7ic.conf
SERVICES := launch_tap.service

.PHONY: clean tapif

tapif: tapif.c tapfirmware.c tapfirmware.h
	$(CC) $(LDFLAGS) $? -o $@

clean:
	rm -f *.o *~ tapif

install: $(EXECS)
	install -d -m 755 $(DESTDIR)$(bindir);			\
	for exec in $(EXECS); do							\
		install $$exec $(DESTDIR)$(bindir);			\
	done;												\
	for script in $(SCRIPTS); do						\
		install $$script $(DESTDIR)$(bindir);			\
	done;												\
	for service in $(SERVICES); do					\
		install $$service $(DESTDIR)$(servicedir);	\
	done;												\
	for config in $(CONFIGS); do						\
		install $$config $(DESTDIR)$(confdir);		\
	done

