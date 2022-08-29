#include <stdint.h>
#include <stdio.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

void registry_global_handler(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version){
    printf("interface: '%s', version: '%u', name: '%u'\n", interface, version, name);
}

void registry_global_remove_handler(void *data, struct wl_registry *registry, uint32_t name){
    printf("removed: %u\n", name);
}

int main(int argc, char *argv[]){
    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Failed to connect to Wayland display.\n");
        return 1;
    }
    fprintf(stderr, "Connection established!\n");

    struct wl_registry *registry = wl_display_get_registry(display);
    struct wl_registry_listener registry_listener = {
        .global = registry_global_handler,
        .global_remove = registry_global_remove_handler
    };
    wl_registry_add_listener(registry, &registry_listener, NULL);

    while(1){
        wl_display_dispatch(display);
    }

    wl_display_disconnect(display);
    return 0;
}
