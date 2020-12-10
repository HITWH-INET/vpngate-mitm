all:udpdecrypt

udpdecrypt:udpdecrypt.c
	gcc -o $@ $^ -lssl -lcrypto

clean:
	rm udpdecrypt
