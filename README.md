# vpngate-mitm
## 1. tlsproxy
### 1.1 Build: go build tlsproxy.go
### 1.2 Usage: tlsproxy -l 443 -r 219.100.37.X:443

## 2. udpdecrypt
### 2.1 Build: make
### 2.2 Dependence: openssl
### 2.2 Usage: 
1) Dump the client key and server key from tlsproxy.
2) Choose an encrypted UDP payload to decrypt.