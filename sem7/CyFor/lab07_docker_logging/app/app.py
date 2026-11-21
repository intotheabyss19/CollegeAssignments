"""Tiny order-service that writes one JSON log line per request to stdout (stdlib only).

Endpoints:  /            ok
            /api/orders  ~15% server errors, ~10% warnings
            /slow        1-3 s latency
            /leak        holds on to 16 MiB per call -> eventually OOM-killed under mem_limit
            /crash       exits the process (restart policy brings it back)
"""
import json
import os
import random
import sys
import time
import uuid
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

SERVICE = os.environ.get("SERVICE_NAME", "orders")
_leak = []


def log(level, msg, **fields):
    rec = {"ts": time.strftime("%Y-%m-%dT%H:%M:%S%z"), "level": level, "service": SERVICE, "msg": msg, **fields}
    sys.stdout.write(json.dumps(rec) + "\n")
    sys.stdout.flush()


class Handler(BaseHTTPRequestHandler):
    def log_message(self, *args):  # silence the default access log; we log JSON instead
        pass

    def _reply(self, status, body, level="INFO", msg="request served", **extra):
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.end_headers()
        self.wfile.write(json.dumps(body).encode())
        log(level, msg, path=self.path, status=status, client=self.client_address[0],
            latency_ms=round((time.time() - self.t0) * 1000, 1), request_id=self.rid, **extra)

    def do_GET(self):
        self.t0, self.rid = time.time(), uuid.uuid4().hex[:12]
        if self.path == "/":
            return self._reply(200, {"ok": True})
        if self.path.startswith("/api/orders"):
            r = random.random()
            if r < 0.15:
                return self._reply(500, {"error": "db timeout"}, "ERROR", "order lookup failed",
                                   error="TimeoutError: postgres:5432 did not respond in 2000 ms")
            if r < 0.25:
                return self._reply(200, {"orders": []}, "WARN", "slow downstream, served from cache")
            return self._reply(200, {"orders": [random.randint(1000, 9999)]})
        if self.path == "/slow":
            time.sleep(random.uniform(1, 3))
            return self._reply(200, {"ok": True}, "WARN", "slow request")
        if self.path == "/leak":
            _leak.append(b"x" * (16 * 1024 * 1024))   # written bytes, so the pages are really used
            return self._reply(200, {"held_mib": 16 * len(_leak)}, "WARN", "memory grew",
                               held_mib=16 * len(_leak))
        if self.path == "/crash":
            self._reply(500, {"bye": True}, "FATAL", "unrecoverable state, exiting")
            os._exit(1)
        return self._reply(404, {"error": "not found"}, "WARN", "unknown route")


if __name__ == "__main__":
    log("INFO", "service starting", port=8080, pid=os.getpid())
    ThreadingHTTPServer(("0.0.0.0", 8080), Handler).serve_forever()
