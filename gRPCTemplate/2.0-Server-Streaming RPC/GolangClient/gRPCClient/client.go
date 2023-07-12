package grpc

import (
	"context"
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"io"
	"log"
)

var (
	Client ServerStreamingRPCClient
)

func Init() *grpc.ClientConn {
	// 连接到服务器
	conn, err := grpc.Dial("localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("failed to dial: %v", err)
	}

	// 创建一个新的客户端
	Client = NewServerStreamingRPCClient(conn)

	return conn
}

func Test(content string) error {
	stream, err := Client.Test(context.Background(), &Request{Request: content})
	if err != nil {
		return err
	}

	for {
		response, err := stream.Recv()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalf("Error receiving response: %v", err)
		}
		fmt.Println("Received data:", response.Reply)
	}

	return nil
}

func TestDemo(content string) ([]string, error) {
	stream, err := Client.Test(context.Background(), &Request{Request: content})
	if err != nil {
		return []string{}, err
	}

	replyList := make([]string, 0)
	for {
		response, err := stream.Recv()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalf("Error receiving response: %v", err)
		}
		fmt.Println("Received data:", response.Reply)
		replyList = append(replyList, response.Reply)
	}

	// 将响应消息转换为Go结构体并返回
	return replyList, nil
}
