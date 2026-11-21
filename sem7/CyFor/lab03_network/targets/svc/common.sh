#!/bin/bash
# Create the throwaway lab user (credentials come from ../.env) with a home full of bait files.
set -e
if ! id "$LAB_USER" >/dev/null 2>&1; then
  adduser -D -s /bin/sh "$LAB_USER"
  echo "$LAB_USER:$LAB_PASS" | chpasswd
  cp -r /srv/files/. "/home/$LAB_USER/"
  chown -R "$LAB_USER:$LAB_USER" "/home/$LAB_USER"
fi
