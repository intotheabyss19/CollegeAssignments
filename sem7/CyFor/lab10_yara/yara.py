import sys


def load_rules(rule_file):
    rules = []
    current = None
    reading_condition = False

    for line in open(rule_file):
        line = line.strip()

        if line.startswith("rule "):
            name = line.split()[1].replace("{", "")
            current = {"name": name, "strings": {}, "condition": ""}
            rules.append(current)

        if line.startswith("$") and "=" in line:
            var, value = line.split("=", 1)
            value = value.strip()
            if value.startswith("{"):
                current["strings"][var.strip()] = bytes.fromhex(value.strip("{} "))
            else:
                current["strings"][var.strip()] = value.strip('"').encode()

        if reading_condition and line and line != "}":
            current["condition"] = line.replace("}", "").strip()
            reading_condition = False

        if "condition:" in line:
            current["condition"] = line.split("condition:")[1].replace("}", "").strip()
            reading_condition = current["condition"] == ""

    return rules


def check(word, rule, found):
    if word == "true":
        return True
    if word == "false":
        return False
    if word == "any of them":
        return len(found) > 0
    if word == "all of them":
        return len(found) == len(rule["strings"])
    return word in found


def rule_matches(rule, data):
    found = [var for var, pattern in rule["strings"].items() if pattern in data]

    for part in rule["condition"].split(" or "):
        if all(check(word.strip(), rule, found) for word in part.split(" and ")):
            return True
    return False


if len(sys.argv) != 3:
    print("usage: python3 yara.py <rule_file> <target_file>")
    sys.exit(1)

rules = load_rules(sys.argv[1])
data = open(sys.argv[2], "rb").read()

for rule in rules:
    if rule_matches(rule, data):
        print(rule["name"], sys.argv[2])
