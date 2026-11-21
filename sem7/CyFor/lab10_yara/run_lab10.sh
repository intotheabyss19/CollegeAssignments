#!/usr/bin/env bash
# Lab 10 (YARA) - one-shot. Installs YARA in a throwaway Ubuntu container and runs all
# three rules against the sample files. Nothing is installed on the Mac.
# Usage:  cd lab10_yara && ./run_lab10.sh
set -e
cd "$(dirname "$0")"
docker run --rm -v "$PWD:/lab" -w /lab ubuntu:24.04 bash -c '
  echo "[*] installing yara in container ..." >&2
  apt-get update -qq >/dev/null 2>&1
  DEBIAN_FRONTEND=noninteractive apt-get install -y -qq yara >/dev/null 2>&1

  echo "============================================================"
  echo " [01] YARA VERSION"
  echo "============================================================"
  yara --version

  echo
  echo "============================================================"
  echo " [A] STRING RULE   rules/rule_a_strings.yar   (condition: 2 of them)"
  echo "============================================================"
  cat rules/rule_a_strings.yar
  echo "--- run against samples/ ---"
  for f in samples/*; do r=$(yara rules/rule_a_strings.yar "$f"); [ -n "$r" ] && echo "MATCH     $r" || echo "no match  $f"; done

  echo
  echo "============================================================"
  echo " [B] CASE-INSENSITIVE RULE   rules/rule_b_nocase.yar   ( (a or b) and not c )"
  echo "============================================================"
  cat rules/rule_b_nocase.yar
  echo "--- run against samples/ ---"
  for f in samples/*; do r=$(yara rules/rule_b_nocase.yar "$f"); [ -n "$r" ] && echo "MATCH     $r" || echo "no match  $f"; done

  echo
  echo "============================================================"
  echo " [C] HEX + WILDCARD RULE   rules/rule_c_hex.yar   { E2 34 ?? C8 23 FB }"
  echo "============================================================"
  cat rules/rule_c_hex.yar
  echo "--- run against samples/ ---"
  for f in samples/*; do r=$(yara rules/rule_c_hex.yar "$f"); [ -n "$r" ] && echo "MATCH     $r" || echo "no match  $f"; done
' | tee output/run_log.txt
