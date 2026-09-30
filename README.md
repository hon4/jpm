# JPM (JLinux Package Manager)

Current status: BETA / Expiremental

### Repository dir structure (Will Change)

All .txt files must have unix LF newline and end with LF.
- index.txt contains package names, 1 per line.
- versions.txt contains package versions, 1 per line eg "0.0.2".

Example Repository URL:
`http://jlinux.net/repo`

* repo (dir)
  * amd64 (dir)
    * index.txt (file)
    * pkg2 (dir)
      * versions.txt (file)
      * 0.0.2.jpm (file)
