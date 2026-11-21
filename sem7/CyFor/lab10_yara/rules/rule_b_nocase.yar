rule Malware_Keywords_NoCase
{
    meta:
        description = "Case-insensitive keyword match using and / or / not"
    strings:
        $a = "malware"  nocase
        $b = "trojan"   nocase
        $c = "backdoor" nocase
    condition:
        ($a or $b) and not $c
}
