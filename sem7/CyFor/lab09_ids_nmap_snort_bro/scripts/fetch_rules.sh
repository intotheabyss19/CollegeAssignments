#!/bin/bash
# Download public rule sets into ./rules (mounted read-only into the Snort containers).
#   Talos community rules  - free, no account, Snort 3 format            (used by default)
#   Proofpoint ET Open     - free, written for Snort 2.9 -> converted to Snort 3 with snort2lua
#                            (used when ET=1 is set, see scripts/analyze.sh)
# Rule sets change daily, so record what we got: date, URL, SHA-256 -> rules/SOURCES.txt
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p rules && cd rules
log() { printf '%s  %s  %s\n' "$(date -u +%FT%TZ)" "$(shasum -a 256 "$2" | cut -c1-64)" "$1" | tee -a SOURCES.txt; }

url=https://www.snort.org/downloads/community/snort3-community-rules.tar.gz
curl -fsSL -o community.tar.gz "$url" && log "$url" community.tar.gz
rm -rf snort3-community-rules && tar xzf community.tar.gz && rm community.tar.gz

url=https://rules.emergingthreats.net/open/snort-2.9.0/emerging-all.rules
mkdir -p et-open
curl -fsSL -o et-open/emerging-all.rules "$url" && log "$url" et-open/emerging-all.rules
# snort2lua -c converts a Snort 2 rules file to Snort 3 syntax; lines it can't convert are kept
# commented out with an explanation.
docker run --rm -v "$PWD/et-open:/et" cyfor/lab09-snort:3.12.4.0 \
  snort2lua -c /et/emerging-all.rules -r /et/emerging-all.snort3.rules -e /et/snort2lua_errors.txt >/dev/null 2>&1 || true
# A handful of converted rules still fail to compile (e.g. a PCRE escape PCRE2 rejects) and one bad
# rule makes Snort refuse the whole config. Ask Snort which lines fail, comment them out, repeat.
for _ in 1 2 3 4 5; do
  bad=$(docker run --rm -v "$PWD/../snort:/lab/snort:ro" -v "$PWD:/lab/rules:ro" -e ET=1 cyfor/lab09-snort:3.12.4.0 \
          snort -c /lab/snort/lab.lua -T 2>&1 | sed -n 's|^ERROR: /lab/rules/et-open/emerging-all.snort3.rules:\([0-9]*\) .*|\1|p' || true)
  [ -z "$bad" ] && break
  for n in $bad; do sed -i.bak "${n}s/^/# LAB-DISABLED (does not compile in Snort 3): /" et-open/emerging-all.snort3.rules; done
  rm -f et-open/*.bak; echo "disabled ET rule line(s): $bad"
done

echo
echo "community rules: $(grep -c '^alert' snort3-community-rules/snort3-community.rules) enabled, $(grep -c '^# alert' snort3-community-rules/snort3-community.rules) disabled"
echo "ET Open (converted): $(grep -cE '^(alert|drop|block)' et-open/emerging-all.snort3.rules) active rules"
