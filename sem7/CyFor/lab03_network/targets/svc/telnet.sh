#!/bin/bash
# Telnet: everything, including the password, crosses the wire in cleartext.
source /opt/svc/common.sh
exec telnetd -F -p 23 -l /bin/login
