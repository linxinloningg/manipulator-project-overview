package grpc

import (
	"context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"log"
	"time"
)

var (
	Client SimpleRPCClient
)

func Init() *grpc.ClientConn {
	// 连接到服务器
	conn, err := grpc.Dial("localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("failed to dial: %v", err)
	}

	// 创建一个新的客户端
	Client = NewSimpleRPCClient(conn)

	return conn
}

func Test(content string) (Reply, error) {
	ctx, cancel := context.WithTimeout(context.Background(), 4*time.Second)
	defer cancel()
	response, err := Client.Test(ctx, &Request{Request: content})
	if err != nil {
		return Reply{}, err
	}
	// 将响应消息转换为Go结构体并返回
	return Reply{
		Reply: response.Reply,
	}, nil
}
