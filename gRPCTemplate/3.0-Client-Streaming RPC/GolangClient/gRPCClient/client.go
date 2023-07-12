package grpc

import (
	"context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"log"
)

var (
	Client ClientStreamingRPCClient
)

func Init() *grpc.ClientConn {
	// 连接到服务器
	conn, err := grpc.Dial("localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("failed to dial: %v", err)
	}

	// 创建一个新的客户端
	Client = NewClientStreamingRPCClient(conn)

	return conn
}

func Test(contents []string) (Reply, error) {
	stream, err := Client.Test(context.Background())
	if err != nil {
		return Reply{}, err
	}

	for _, content := range contents {

		err = stream.Send(&Request{Request: content})

	}

	response, err := stream.CloseAndRecv()

	return Reply{
		Reply: response.Reply,
	}, nil
}
