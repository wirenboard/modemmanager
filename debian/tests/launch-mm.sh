#!/bin/bash
# allow ModemManager to start inside a container
mkdir -p /etc/systemd/system/ModemManager.service.d/
cat <<EOF > /etc/systemd/system/ModemManager.service.d/override.conf
[Unit]
ConditionVirtualization=
EOF
systemctl daemon-reload
systemctl start ModemManager.service
