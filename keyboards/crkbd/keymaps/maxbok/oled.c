#include <stdio.h>
#include "transactions.h"
#include "maxbok.h"

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

bool is_locked;
Label host_name;
Label time;
Label date;
// Report cpu_usage_report;

void reset_states(void) {
    is_locked = false;
    host_name = (Label) { "", 0, false };
    time = (Label) { "", 6, false };
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

void keyboard_post_init_user(void) {
    transaction_register_rpc(SYNC_HOST_NAME, sync_host_name);
    transaction_register_rpc(SYNC_DATE, sync_date);
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

void housekeeping_task_user(void) {
    if (is_keyboard_master());
    else { return; }

    housekeeping_sync_host_name();
    housekeeping_sync_date();
}

// Render

void render_master(void) {
    if (is_locked) {
        oled_clear();
        return;
    }

    if (time.changed);
    else { return; }

    oled_write_ln(time.value, false);
    time.changed = false;
}

void render_slave(void) {
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
    uint8_t day = report.data[2];
    uint8_t month = report.data[3];
    uint8_t year1 = report.data[4];
    uint8_t year2 = report.data[5];
    uint16_t year = ((uint16_t)year2 << 8) | year1;

    sprintf(time.value, "%02uh%02u", hour, minute);
    time.value[5] = '\0';
    time.changed = true;

    sprintf(date.value, "%02u/%02u/%04u", day, month, year);
    date.value[10] = '\0';
    date.changed = true;
}

void cpu_usage_from_report(Report report) {
    // cpu_usage_report = report;
}

// Receive raw hid

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 2); else { return; }

    Report report = build_report(data, length);

    is_locked = false;
    switch (report.type) {
        case 0:
            reset_states();
            is_locked = true;
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

