find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC REQUIRED)


get_filename_component(proto_file "${CMAKE_CURRENT_SOURCE_DIR}/proto/points.proto" ABSOLUTE)
get_filename_component(proto_path "${proto_file}" PATH)

# Generated sources
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/points.pb.cc")
# set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/points.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/points.grpc.pb.cc")
# set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/points.grpc.pb.h")
add_custom_command(
      OUTPUT "${proto_srcs}" "${grpc_srcs}"
      COMMAND $<TARGET_FILE:protobuf::protoc>
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${proto_path}"
        --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        "${proto_file}"
      DEPENDS "${proto_file}")

add_library(publisher 
publisher.cc
${proto_srcs}
${grpc_srcs})

target_include_directories(publisher PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})

target_link_libraries(publisher
gRPC::grpc++
gRPC::grpc++_reflection)