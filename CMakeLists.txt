project(wlbox)

add_executable(client client.c)
add_executable(server server.c)

target_link_libraries(client wayland-client)
target_link_libraries(server wayland-server)
