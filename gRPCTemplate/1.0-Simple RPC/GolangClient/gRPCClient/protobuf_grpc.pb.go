// Code generated by protoc-gen-go-grpc. DO NOT EDIT.
// versions:
// - protoc-gen-go-grpc v1.3.0
// - protoc             v4.22.2
// source: protobuf.proto

package grpc

import (
	context "context"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
)

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
// Requires gRPC-Go v1.32.0 or later.
const _ = grpc.SupportPackageIsVersion7

const (
	SimpleRPC_Test_FullMethodName = "/gprc.SimpleRPC/Test"
)

// SimpleRPCClient is the client API for SimpleRPC service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://pkg.go.dev/google.golang.org/grpc/?tab=doc#ClientConn.NewStream.
type SimpleRPCClient interface {
	Test(ctx context.Context, in *Request, opts ...grpc.CallOption) (*Reply, error)
}

type simpleRPCClient struct {
	cc grpc.ClientConnInterface
}

func NewSimpleRPCClient(cc grpc.ClientConnInterface) SimpleRPCClient {
	return &simpleRPCClient{cc}
}

func (c *simpleRPCClient) Test(ctx context.Context, in *Request, opts ...grpc.CallOption) (*Reply, error) {
	out := new(Reply)
	err := c.cc.Invoke(ctx, SimpleRPC_Test_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

// SimpleRPCServer is the server API for SimpleRPC service.
// All implementations must embed UnimplementedSimpleRPCServer
// for forward compatibility
type SimpleRPCServer interface {
	Test(context.Context, *Request) (*Reply, error)
	mustEmbedUnimplementedSimpleRPCServer()
}

// UnimplementedSimpleRPCServer must be embedded to have forward compatible implementations.
type UnimplementedSimpleRPCServer struct {
}

func (UnimplementedSimpleRPCServer) Test(context.Context, *Request) (*Reply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method Test not implemented")
}
func (UnimplementedSimpleRPCServer) mustEmbedUnimplementedSimpleRPCServer() {}

// UnsafeSimpleRPCServer may be embedded to opt out of forward compatibility for this service.
// Use of this interface is not recommended, as added methods to SimpleRPCServer will
// result in compilation errors.
type UnsafeSimpleRPCServer interface {
	mustEmbedUnimplementedSimpleRPCServer()
}

func RegisterSimpleRPCServer(s grpc.ServiceRegistrar, srv SimpleRPCServer) {
	s.RegisterService(&SimpleRPC_ServiceDesc, srv)
}

func _SimpleRPC_Test_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(Request)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(SimpleRPCServer).Test(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: SimpleRPC_Test_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(SimpleRPCServer).Test(ctx, req.(*Request))
	}
	return interceptor(ctx, in, info, handler)
}

// SimpleRPC_ServiceDesc is the grpc.ServiceDesc for SimpleRPC service.
// It's only intended for direct use with grpc.RegisterService,
// and not to be introspected or modified (even as a copy)
var SimpleRPC_ServiceDesc = grpc.ServiceDesc{
	ServiceName: "gprc.SimpleRPC",
	HandlerType: (*SimpleRPCServer)(nil),
	Methods: []grpc.MethodDesc{
		{
			MethodName: "Test",
			Handler:    _SimpleRPC_Test_Handler,
		},
	},
	Streams:  []grpc.StreamDesc{},
	Metadata: "protobuf.proto",
}
