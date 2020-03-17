#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

SUMMARY = "Simple helloworld application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://gpiol.c"
SRC_URI += "file://gpiol.h"
SRC_URI += "file://main.cpp"
#SRC_URI += "file://main.c"
SRC_URI += "file://gpio_class.h"
SRC_URI += "file://gpio_class.cpp"
SRC_URI += "file://gpio_thread.cpp"
SRC_URI += "file://gpio_thread.h"
SRC_URI += "file://enum.h"
SRC_URI += "file://autorun_gpio.sh"
SRC_URI += "file://gpiol.service"

S = "${WORKDIR}"

# FILES_${PN} += " /opt/* /usr/lib/systemd/*"
FILES_${PN} += " /opt/* /usr/lib/systemd/* ${sysconfdir}/init.d/* ${sysconfdir}/rc5.d/*"

do_compile() {
#	     ${CC} ${LDFLAGS} gpiol.c main.c -o gpiol
#	     ${CXX} ${LDFLAGS} gpio_class.cpp main.cpp gpiol.c -o gpiol
	     ${CXX} ${LDFLAGS}  -Wall -std=c++11 -pthread *.cpp *.c -o gpiol
		#  cat ${WORKDIR}/auterun_gpio.sh > auterun_gpio.sh
		#  cat ${WORKDIR}/gpiol.service > gpiol.service
}

do_install() {
	    install -d ${D}${bindir}
	    install -m 0755 gpiol ${D}${bindir}
	    # install -d ${D}/opt/gpiol
		# install -d ${D}/usr/lib/systemd/user
#	    install -d ${D}/etc/systemd/system
		install -d ${D}${sysconfdir}/init.d
		install -d ${D}${sysconfdir}/rc5.d
		install -m 755 ${WORKDIR}/autorun_gpio.sh ${D}${sysconfdir}/init.d
		ln -s ${sysconfdir}/init.d/autorun_gpio.sh ${D}${sysconfdir}/rc5.d/S98gpiol.sh
		# install -m 755 ${WORKDIR}/autorun_gpio.sh ${D}/opt/gpiol
		# install -m 644 ${WORKDIR}/gpiol.service ${D}/usr/lib/systemd/user
}
