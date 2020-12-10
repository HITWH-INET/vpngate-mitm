package main
import (
	"crypto/tls"
	"log"
	"net"
	"fmt"
	"flag"
	"encoding/hex"
	"os"
)
var (
	version    = "0.0.1"
	listenPort = flag.String("l", "443", "local address")
	remoteAddr = flag.String("r", "219.100.37.124:443", "remote address")
)

func main() {
	//Parse arguments
	flag.Parse()

	//Load Key Pair
	cert, err := tls.LoadX509KeyPair("mitm.crt", "mitm.key")
	if err != nil {
		log.Println(err)
		return
	}
	//Enable SSL Keylog
	keylog, _:= os.OpenFile("tls-secrets.txt", os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)
	config := &tls.Config{
		Certificates: []tls.Certificate{cert},
		InsecureSkipVerify: true,
		KeyLogWriter: keylog,
		MaxVersion: 0x0303,
	}

	ln, err := tls.Listen("tcp", ":" + *listenPort, config)
	if err != nil {
		log.Println(err)
		return
	}
	defer ln.Close()
	for {
		//A new connection from Client to Mitm
		connC2M, err := ln.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go processConnection(connC2M, config)
	}
}

func processConnection(connClient net.Conn, config *tls.Config){
	log.Println("New Connection from Client to Mitm.")
	//Create connection from Mitm to server
	connServer, err := tls.Dial("tcp", *remoteAddr, config)
	if err != nil {
		log.Println(err)
	}
	log.Println("New Connection from Mitm to Server.")

	go processDataFromSourceToDest(connClient, connServer)
	go processDataFromSourceToDest(connServer, connClient)

}
func processDataFromSourceToDest(connSrc net.Conn, connDst net.Conn ){
	buf := make([]byte, 65536)
	for {
		n, err := connSrc.Read(buf[:])
		if err != nil {
			log.Println(err)
			return
		}
		wn,err := connDst.Write(buf[:n])
		if err != nil {
			log.Println(err)
			return
		}
		if wn == 0{
			log.Println("Write 0 bytes")
		}
		processVPNGate(buf[:n])
	}
}
func processVPNGate(data []byte ){
	fmt.Println(hex.Dump(data[:]))
}

