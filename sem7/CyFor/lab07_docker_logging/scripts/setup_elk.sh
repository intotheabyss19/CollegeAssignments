#!/bin/sh
# One-shot ELK setup (runs in the `setup` container):
#   step 10: ILM policy - roll indices daily (logstash_format) and DELETE them after 7 days
#   index template so every docker-logs-* index gets that policy and sensible field types
#   step 8 : Kibana data view "docker-logs-*" so Discover/Lens work straight away
ES=http://elasticsearch:9200; KB=http://kibana:5601
set -e

echo "[setup] ILM policy docker-logs-retention (warm after 1d, delete after 7d)"
curl -fsS -X PUT "$ES/_ilm/policy/docker-logs-retention" -H 'Content-Type: application/json' -d '{
  "policy": { "phases": {
    "hot":    { "actions": {} },
    "warm":   { "min_age": "1d", "actions": { "forcemerge": { "max_num_segments": 1 } } },
    "delete": { "min_age": "7d", "actions": { "delete": {} } }
  } } }'; echo

echo "[setup] index template docker-logs"
curl -fsS -X PUT "$ES/_index_template/docker-logs" -H 'Content-Type: application/json' -d '{
  "index_patterns": ["docker-logs-*"],
  "template": {
    "settings": { "number_of_replicas": 0, "index.lifecycle.name": "docker-logs-retention" },
    "mappings": { "properties": {
      "@timestamp": { "type": "date" },
      "level":      { "type": "keyword" },
      "service":    { "type": "keyword" },
      "path":       { "type": "keyword" },
      "status":     { "type": "integer" },
      "latency_ms": { "type": "float" },
      "container_name": { "type": "keyword" }
    } }
  } }'; echo

echo "[setup] Kibana data view docker-logs-*"
curl -fsS -X POST "$KB/api/data_views/data_view" -H 'kbn-xsrf: true' -H 'Content-Type: application/json' -d '{
  "data_view": { "id": "docker-logs", "title": "docker-logs-*", "name": "Docker container logs", "timeFieldName": "@timestamp" },
  "override": true }' >/dev/null && echo "ok"

echo "[setup] done - open http://localhost:5601/app/discover"
