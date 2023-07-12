package main

import (
	"SimpleRPC/gRPCClient"
	"fmt"
)

func main() {
	conn := grpc.Init()

	r, _ := grpc.Test("Hello World!")

	fmt.Printf("%s", r.Reply)

	err := conn.Close()
	if err != nil {
		panic(err)
	}
}
