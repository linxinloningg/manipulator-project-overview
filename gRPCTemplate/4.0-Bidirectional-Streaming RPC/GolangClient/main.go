package main

import (
	grpc "BidirectionalStreamingRPC/gRPCClient"
)

func main() {
	conn := grpc.Init()

	_ = grpc.Test()

	err := conn.Close()

	if err != nil {
		panic(err)
	}
}
