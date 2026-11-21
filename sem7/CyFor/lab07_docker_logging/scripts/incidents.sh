#!/usr/bin/env bash
# Steps 11-12: cause four realistic incidents, then find each one in the logs/metrics.
# Run on the Mac from anywhere; it talks to the containers through `docker compose exec`.
set -uo pipefail
cd "$(dirname "$0")/.."
OUT=output; mkdir -p "$OUT"
LOG="$OUT/incidents_timeline.txt"
hit() { docker compose exec -T loadgen curl -s -o /dev/null -w '%{http_code}' "http://$1:8080$2" 2>/dev/null; }
note() { echo "[$(date -u +%H:%M:%S)Z] $*" | tee -a "$LOG"; }
: >"$LOG"

note "INCIDENT 1 - error burst: 60 rapid /api/orders calls on orders"
for i in $(seq 1 60); do hit orders /api/orders >/dev/null; done

note "INCIDENT 2 - crash loop: /crash on inventory (restart policy brings it back)"
hit inventory /crash; sleep 3; hit inventory /crash; sleep 3

note "INCIDENT 3 - memory leak: /leak on orders until the 96 MiB limit OOM-kills it"
for i in $(seq 1 10); do printf '%s ' "$(hit orders /leak)"; done; echo
sleep 3

note "INCIDENT 4 - resource contention: 90 s stress-ng noisy neighbour"
docker compose --profile stress up -d stress >/dev/null 2>&1
sleep 10
echo "--- docker stats snapshot during contention" | tee -a "$LOG"
docker stats --no-stream --format 'table {{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.MemPerc}}' $(docker compose --profile stress ps -q) | tee -a "$LOG"

echo | tee -a "$LOG"
echo "=== How each incident shows up ===" | tee -a "$LOG"
echo "--- restarts / OOM kills (docker inspect)" | tee -a "$LOG"
for s in orders inventory; do
  docker inspect --format "$s: restarts={{.RestartCount}} (OOMKilled resets after an automatic restart - use the oom event below)" "$(docker compose ps -q $s)" | tee -a "$LOG"
done
echo "--- docker events (die / oom / start) in the last 3 minutes" | tee -a "$LOG"
docker events --since 3m --until 0s --filter type=container --filter event=die --filter event=oom --filter event=start \
  --filter label=com.docker.compose.project=cyfor-lab07 \
  --format '{{.Time}} {{.Action}} {{.Actor.Attributes.name}} exitCode={{index .Actor.Attributes "exitCode"}}' |
  while read -r t rest; do echo "$(date -u -r "$t" +%H:%M:%SZ) $rest"; done | tee -a "$LOG"
echo "--- error counts per service in Elasticsearch (last 15 min)" | tee -a "$LOG"
curl -s -H 'Content-Type: application/json' 'http://127.0.0.1:9200/docker-logs-*/_search?size=0' -d '{
  "query": {"range": {"@timestamp": {"gte": "now-15m"}}},
  "aggs": {"by_service": {"terms": {"field": "service"}, "aggs": {"by_level": {"terms": {"field": "level"}}}}}}' |
  python3 -c 'import sys, json
for b in json.load(sys.stdin)["aggregations"]["by_service"]["buckets"]:
    levels = ", ".join("%s=%d" % (l["key"], l["doc_count"]) for l in b["by_level"]["buckets"])
    print("%-10s %s" % (b["key"], levels))' | tee -a "$LOG"
echo "--- FATAL lines from the json-file driver (inventory)" | tee -a "$LOG"
docker compose logs --no-log-prefix inventory 2>/dev/null | grep FATAL | tail -3 | tee -a "$LOG"
echo "--- payments errors in the central syslog file" | tee -a "$LOG"
grep -c '"level": "ERROR"' output/syslog/payments.log | sed 's/^/ERROR lines: /' | tee -a "$LOG"
echo
echo "[saved] $LOG   (now find the same incidents in Kibana: http://localhost:5601/app/discover)"
