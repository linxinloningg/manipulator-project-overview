package main

import (
	grpc "ClientStreamingRPC/gRPCClient"
	"fmt"
)

func main() {
	conn := grpc.Init()

	r, _ := grpc.Test([]string{"1", "2", "3"})

	fmt.Printf("%s", r.Reply)

	err := conn.Close()

	if err != nil {
		panic(err)
	}
}
