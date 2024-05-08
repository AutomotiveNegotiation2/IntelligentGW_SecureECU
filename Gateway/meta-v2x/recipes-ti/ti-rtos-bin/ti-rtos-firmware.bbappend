

FILESEXTRAPATHS_prepend := "${TOPDIR}/../../j7_v2x-mirror/${PN}:"
SRC_URI += "file://app_remoteswitchcfg_server_strip.xer5f"
SRCPV = "1.0"


do_install_prepend() {
	cp -f ${WORKDIR}/app_remoteswitchcfg_server_strip.xer5f ${WORKDIR}/git/ti-eth/j721e
}
