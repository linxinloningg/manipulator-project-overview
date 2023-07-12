package grpc

import (
	"context"
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"log"
)

var (
	Client BidirectionalStreamingRPCClient
)

func Init() *grpc.ClientConn {
	// 连接到服务器
	conn, err := grpc.Dial("localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("failed to dial: %v", err)
	}

	// 创建一个新的客户端
	Client = NewBidirectionalStreamingRPCClient(conn)

	return conn
}

func Test() error {
	var content string
	stream, err := Client.Test(context.Background())
	if err != nil {
		return err
	}

	done := make(chan bool)

	log.Printf("Start! \n")

	go func() {
		for {
			reply, err := stream.Recv()
			if err != nil {
				log.Fatalf("%v.Test(_) = _, %v", Client, err)
			}
			log.Printf("Received message: %s\n", reply.GetReply())
		}
	}()

	go func() {
		for {
			_, _ = fmt.Scanln(&content)
			request := &Request{Request: content}
			err := stream.Send(request)
			if err != nil {
				log.Fatalf("%v.Send(%v) = %v", stream, request, err)
			}
			log.Printf("Send message: %s\n", content)
		}

	}()

	<-done

	return nil

}
