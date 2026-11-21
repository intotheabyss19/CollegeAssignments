#!/usr/bin/env bash
# Steps 1-6 and 9-10 evidence: which logging driver/options each container uses, where the
# json-file logs live, and proof that rotation works. Run on the Mac from the lab07 folder.
set -uo pipefail
cd "$(dirname "$0")/.."
OUT=output; mkdir -p "$OUT"
REPORT="$OUT/logging_inventory.txt"

{
echo "== Daemon default logging driver"
docker info --format '{{.LoggingDriver}}'
echo
echo "== Per-container logging configuration (docker inspect)"
printf '%-28s %-10s %s\n' CONTAINER DRIVER OPTIONS
for c in $(docker compose ps -q); do
  docker inspect --format '{{.Name}}|{{.HostConfig.LogConfig.Type}}|{{json .HostConfig.LogConfig.Config}}' "$c"
done | sort | awk -F'|' '{printf "%-28s %-10s %s\n", substr($1,2), $2, $3}'
echo
echo "== Where json-file logs are stored (inside the Docker Desktop VM)"
for c in $(docker compose ps -q inventory loadgen); do docker inspect --format '{{.Name}} -> {{.LogPath}}' "$c"; done
echo
echo "== Rotation on disk for 'inventory' (max-size 200k, max-file 3, compress)"
ID=$(docker compose ps -q inventory)
docker run --rm -v /var/lib/docker/containers:/c:ro alpine:3.20 sh -c "ls -la /c/$ID/ | grep json"
echo
echo "== 'docker logs' still works with json-file (last 3 lines of inventory)"
docker compose logs --no-log-prefix --tail 3 inventory
echo
echo "== 'docker logs' on payments (syslog driver) - only works because of Docker's 'dual logging'"
echo "   local cache (Docker 20.10+); with older engines, remote drivers had no 'docker logs' at all"
docker logs --tail 3 "$(docker compose ps -q payments)" 2>&1 | head -3
echo
echo "== Central collectors"
echo "-- syslog files:"; ls -la output/syslog/
echo "-- fluentd archive:"; find output/fluentd-archive -type f 2>/dev/null | head
echo "-- Elasticsearch indices:"; curl -s 'http://127.0.0.1:9200/_cat/indices/docker-logs-*?v&h=index,docs.count,store.size'
echo "-- ILM policy attached:"; curl -s 'http://127.0.0.1:9200/docker-logs-*/_ilm/explain?filter_path=indices.*.policy,indices.*.phase'
echo
} 2>&1 | tee "$REPORT"
echo "[saved] $REPORT"
