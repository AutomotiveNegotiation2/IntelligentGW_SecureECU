SUMMARY = "v2x config"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://v2x-config.service \
			file://v2x_init_script.sh \
		  "

SRCREV = "${AUTOREV}"
S = "${WORKDIR}"
inherit systemd


# for systemd
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "v2x-config.service"


do_install() {
	install -d ${D}/${systemd_system_unitdir}
	install -m 0644 ${WORKDIR}/v2x-config.service ${D}/${systemd_system_unitdir}
	
	mkdir -p ${D}/usr/bin
	install -m 0755 v2x_init_script.sh ${D}/usr/bin
}

INSANE_SKIP_${PN} += "ldflags file-rdeps"
FILES_${PN} += " \
			/usr/bin \
			${systemd_system_unitdir} \
			"