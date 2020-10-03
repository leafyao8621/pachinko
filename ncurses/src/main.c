#include "controller/controller.h"

int main(void) {
    controller_initialize();
    for (; controller_handle_key_press(););
    controller_finalize(); 
    return 0;
}
