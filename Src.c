#include <psl1ght.h>
#include <sys/console.h>
#include <sys/timer.h>
#include <controller_api.h>  // Use the appropriate library for controller interaction

void update_leds(int battery_level) {
    int led_status = 0;

    // Determine LED status based on battery level
    if (battery_level > 75) {
        led_status = 0x0F; //all LEDs on
    } else if (battery_level > 50) {
        led_status = 0x07; //3 LEDs on
    } else if (battery_level > 25) {
        led_status = 0x03; //2 LEDs on
    } else {
        led_status = 0x01; //1 LED on
    }
set_controller_led(led_status);
}
void check_battery_status() {
    int battery_level = get_battery_level(); // Assume this function gets the battery level
    int is_charging = is_controller_charging(); // Assume this function checks if the controller is charging

    if (is_charging) {
        update_leds(battery_level);
    } else {
        set_controller_led(0x00); // Turn off all LEDs when not charging
    }
}

int main() {
    while (1) {
        check_battery_status();
        sys_timer_usleep(1000000); // Sleep for 1 second
    }

    return 0;
}