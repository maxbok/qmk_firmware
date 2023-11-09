#include <stdio.h>
#include "maxbok.h"

typedef struct Report {
    uint8_t type;
    uint8_t size;
    uint8_t data[30];
} Report;

typedef struct HostName {
    char value[12];
    bool changed;
} HostName;

typedef struct DateTime {
    char time[6];
    char date[11];
    bool changed;
} DateTime;

bool is_locked;
HostName host_name;
DateTime date_time;
// Report cpu_usage_report;

void reset_states(void) {
    is_locked = false;
    host_name = (HostName) { "", false };
    date_time = (DateTime) { "", "", false };
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

// Render

void render_master(void) {
    if (is_locked) {
        oled_clear();
        return;
    }

    if (host_name.changed || date_time.changed);
    else { return; }

    oled_clear();

    oled_write_ln(host_name.value, false);
    oled_write_ln("\n", false);
    host_name.changed = false;

    oled_write_ln(date_time.time, false);
    oled_write_ln(date_time.date, false);
    date_time.changed = false;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master();
    } else {
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
    host_name.changed = true;
}

void date_time_from_report(Report report) {
    uint8_t hour = report.data[0];
    uint8_t minute = report.data[1];
    uint8_t day = report.data[2];
    uint8_t month = report.data[3];

    sprintf(date_time.time, "%02uh%02u", hour, minute);
    date_time.time[5] = '\0';
    sprintf(date_time.date, "%02u/%02u/2023", day, month);
    date_time.date[10] = '\0';
    date_time.changed = true;
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

