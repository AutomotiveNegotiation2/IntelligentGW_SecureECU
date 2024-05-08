
FILESEXTRAPATHS_prepend := "${TOPDIR}/../../j7_v2x-mirror/${PN}:"

SRC_URI = "file://git"
SRCREV = "${AUTOREV}"
SRCPV = "2021.01"
PR = ""


do_patch[noexec] = "1"

do_compile_prepend() {
    ## sed -e 's%dorprocboot=0%dorprocboot=1%g' -i ${S}/include/environment/ti/k3_rproc.h
}