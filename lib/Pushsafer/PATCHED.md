Pushsafer Arduino library v1.1.0 (appzer/pushsafer-arduino-library @ 7389867, Feb 2020),
vendored with the SSL change described in pushSafer.ino:

- Pushsafer.h: enable `#define SSL_PORT 443`, disable `#define PORT 80`
- Pushsafer.cpp: connect with `SSL_PORT` instead of `PORT`
