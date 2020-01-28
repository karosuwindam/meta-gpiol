#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

SUMMARY = "Simple helloworld application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://gpiol.c"
SRC_URI = "file://gpiol.h"
SRC_URI = "file://main.c"


S = "${WORKDIR}"

do_compile() {
	     ${CC} ${LDFLAGS} gpiol.c main.c -o gpiol
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 gpiol ${D}${bindir}
}
