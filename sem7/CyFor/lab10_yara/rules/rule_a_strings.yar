rule SuspiciousScript_Strings
{
    meta:
        description = "Flags a file holding known malicious-script indicators"
        author      = "Yash Gupta B230038CS"
    strings:
        $s1 = "powershell -enc"
        $s2 = "Invoke-WebRequest"
        $s3 = "cmd.exe /c"
    condition:
        2 of them
}
