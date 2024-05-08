
FILESEXTRAPATHS_prepend := "${TOPDIR}/../../j7_v2x-mirror/${PN}:"
SRC_URI = "file://git \
           file://defconfig \
		   "
SRCREV = "${AUTOREV}"
SRCPV = "5.10"
PR = ""


do_patch[noexec] = "1"
KERNEL_LOCALVERSION = "5.10"

##KERNEL_DEVICETREE_append = " ti/k3-j721e-gesi-exp-board.dtbo"
##KERNEL_DEVICETREE_append = " ti/k3-j721e-quad-port-eth-exp.dtbo"