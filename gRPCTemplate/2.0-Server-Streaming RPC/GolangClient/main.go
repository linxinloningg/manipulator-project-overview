package main

import grpc "ServerStreamingRPC/gRPCClient"

func main() {
	conn := grpc.Init()

	_ = grpc.Test("start")

	err := conn.Close()
	if err != nil {
		panic(err)
	}
}
