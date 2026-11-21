rule Hex_Signature_Wildcard
{
    meta:
        description = "Hex byte signature with a wildcard (??) for a byte that varies"
    strings:
        $sig = { E2 34 ?? C8 23 FB }
    condition:
        $sig
}
