#include <stdio.h>
#include <math.h>
#include "transactions.h"
#include "maxbok.h"
#include "oled_assets.h"

typedef struct Report {
    uint8_t type;
    uint8_t size;
    uint8_t data[30];
} Report;

typedef struct Label {
    char value[12];
    uint8_t length;
    bool changed;
} Label;

typedef struct Time {
    uint8_t hour;
    uint8_t minute;
    bool changed;
} Time;

typedef struct Lock {
    bool value;
    bool changed;
} Lock;

Lock is_locked;
Label host_name;
Time time;
Label date;
// Report cpu_usage_report;

void reset_states(void) {
    is_locked = (Lock) { false, false };
    host_name = (Label) { "", 0, false };
    time = (Time) { 0, 0, false };
    date = (Label) { "", 11, false };
}

// Orientation

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    reset_states();

    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

// Transaction

void sync_host_name(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const Label *received_host_name = (const Label *)in_data;

    if (host_name.value != received_host_name->value);
    else { return; }

    memcpy(host_name.value, received_host_name->value, received_host_name->length);
    host_name.value[received_host_name->length] = '\0';
    host_name.changed = true;
}

void sync_date(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const Label *received_date = (const Label *)in_data;

    if (date.value != received_date->value);
    else { return; }

    memcpy(date.value, received_date->value, received_date->length);
    date.value[received_date->length] = '\0';
    date.changed = true;
}

void sync_is_locked(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const Lock *received_is_locked = (const Lock *)in_data;

    if (is_locked.value != received_is_locked->value);
    else { return; }

    is_locked.value = received_is_locked->value;
    is_locked.changed = true;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(SYNC_HOST_NAME, sync_host_name);
    transaction_register_rpc(SYNC_DATE, sync_date);
    transaction_register_rpc(SYNC_IS_LOCKED, sync_is_locked);
}

void housekeeping_sync_host_name(void) {
    // Interact with slave every 1s
    static uint32_t last_host_name_sync = 0;
    if (
            host_name.changed && 
            timer_elapsed32(last_host_name_sync) > 1000 &&
            transaction_rpc_send(SYNC_HOST_NAME, sizeof(host_name), &host_name)
       );
    else { return; }
        
    host_name.changed = false;
    last_host_name_sync = timer_read32();
}

void housekeeping_sync_date(void) {
    // Interact with slave every 1s
    static uint32_t last_date_sync = 0;
    if (
            date.changed && 
            timer_elapsed32(last_date_sync) > 1000 &&
            transaction_rpc_send(SYNC_DATE, sizeof(date), &date)
       );
    else { return; }
        
    date.changed = false;
    last_date_sync = timer_read32();
}

void housekeeping_sync_is_locked(void) {
    // Interact with slave every 1s
    static uint32_t last_is_locked_sync = 0;
    if (
            is_locked.changed &&
            timer_elapsed32(last_is_locked_sync) > 1000 &&
            transaction_rpc_send(SYNC_IS_LOCKED, sizeof(is_locked), &is_locked)
       );
    else { return; }
        
    is_locked.changed = false;
    last_is_locked_sync = timer_read32();
}

void housekeeping_task_user(void) {
    if (is_keyboard_master());
    else { return; }

    housekeeping_sync_host_name();
    housekeeping_sync_date();
    housekeeping_sync_is_locked();
}

// Render

void oled_render_digit(const char *digit, uint8_t x_offset, uint8_t y_offset, uint8_t width, uint8_t height) {
     for (uint8_t x = 0; x < width; x++) {
         for (uint8_t y = 0; y < ceil(height / 8); y++) {
             uint8_t index = x + (y * width);
             for (uint8_t bit = 0; bit < 8; bit++) {
                 oled_write_pixel(x_offset + x, y_offset + y * 8 + bit, digit[index] & (1 << bit));
             }
         }
     }
}

void oled_render_large_digit(const char *digit, uint8_t x_index, uint8_t y_index) {
    uint8_t horizontal_margin = 2;
    uint8_t vertical_margin = 4;

    oled_render_digit(
            digit, 
            x_index * (LARGE_ASSET_WIDTH + horizontal_margin),
            y_index * (LARGE_ASSET_HEIGHT + vertical_margin),
            LARGE_ASSET_WIDTH, 
            LARGE_ASSET_HEIGHT
    );
}

const char *digit_large_asset(uint8_t value) {
    switch (value) {
        case 0:     return large0;
        case 1:     return large1;
        case 2:     return large2;
        case 3:     return large3;
        case 4:     return large4;
        case 5:     return large5;
        case 6:     return large6;
        case 7:     return large7;
        case 8:     return large8;
        case 9:     return large9;
        default:    return large0;
    }
}

void oled_render_time_component(uint8_t component, uint8_t y_index) {
    uint8_t tens = floor(component / 10);
    uint8_t units = component - tens * 10;

    oled_render_large_digit(digit_large_asset(tens), 0, y_index);
    oled_render_large_digit(digit_large_asset(units), 1, y_index);
}

void render_master(void) {
    if (is_locked.value) {
        oled_clear();
        return;
    }

    if (time.changed);
    else { return; }

    oled_render_time_component(time.hour, 0);
    oled_render_time_component(time.minute, 1);
    time.changed = false;
}

void render_slave(void) {
    if (is_locked.value) {
        oled_clear();
        return;
    }

    if (host_name.changed || date.changed);
    else { return; }

    oled_write_ln(host_name.value, false);
    oled_write_ln(date.value, false);

    host_name.changed = false;
    date.changed = false;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master();
    } else {
        render_slave();
    }

    return false;
}

// Reports

Report build_report(uint8_t *data, uint8_t length) {
    Report report;

    uint8_t type = data[0];
    uint8_t size = data[1];

    report.type = type;
    report.size = size;

    for (int i = 0; i < size; i++) {
        report.data[i] = data[2 + i];
    }

    return report;
}

void host_name_from_report(Report report) {
    memcpy(host_name.value, report.data, report.size);
    host_name.value[report.size] = '\0';
    host_name.length = report.size;
    host_name.changed = true;
}

void date_time_from_report(Report report) {
    uint8_t hour = report.data[0];
    uint8_t minute = report.data[1];

    time.hour = hour;
    time.minute = minute;
    time.changed = true;

    uint8_t day = report.data[2];
    uint8_t month = report.data[3];
    uint8_t year1 = report.data[4];
    uint16_t year2 = report.data[5] * 256;
    uint16_t year = year2 + year1;

    sprintf(date.value, "%02u/%02u/%04u", day, month, year);
    date.value[10] = '\0';
    date.changed = true;
}

void cpu_usage_from_report(Report report) {
    // cpu_usage_report = report;
}

void unlock(void) {
    if (is_locked.value); else { return; }
    
    is_locked.value = false;
    is_locked.changed = true;
}

void lock(void) {
    reset_states();
    is_locked.value = true;
    is_locked.changed = true;
}

// Receive raw hid

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 2); else { return; }

    Report report = build_report(data, length);

    unlock();
    switch (report.type) {
        case 0:
            lock();
            break;
        case 1:
            host_name_from_report(report);
            break;
        case 2:
            date_time_from_report(report);
            break;
        case 3:
            cpu_usage_from_report(report);
            break;
        default:
            break;
    }
}

