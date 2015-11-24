#!/bin/bash

echo '## Starting module ##'
modprobe aziokbd
echo '## Attempting to reload usbhid module ##'
rmmod usbhid && modprobe usbhid quirks=$quirk
