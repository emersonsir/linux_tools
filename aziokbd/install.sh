#!/bin/bash
set -x

echo '## Making package ##'
make

echo '## Installing package ##'
make install

quirk='0x0c45:0x7603:0x0007'
modquirk="options usbhid quirks=$quirk"

echo $modquirk >> /etc/modprobe.d/usbhid.conf
echo '## Starting module ##'
modprobe aziokbd

echo '## Attempting to reload usbhid module ##'
rmmod usbhid && modprobe usbhid quirks=$quirk
