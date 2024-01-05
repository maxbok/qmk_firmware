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

typedef struct Date {
    uint8_t day;
    uint8_t month;
    uint16_t year;
    bool changed;
} Date;

typedef struct Lock {
    bool value;
    bool changed;
} Lock;

typedef struct CPUUsage {
    uint8_t cores[20];
    uint8_t count;
    bool changed;
} CPUUsage;

Lock is_locked;
Label host_name;
Time time;
Date date;
CPUUsage cpu_usage;

void reset_states(void) {
    is_locked = (Lock) { false, false };
    host_name = (Label) { "", 0, false };
    time = (Time) { 0, 0, false };
    date = (Date) { 0, 0, 0, false };
    cpu_usage = (CPUUsage) { {}, 0, false };
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
    const Date *received_date = (const Date *)in_data;

    if (date.day != received_date->day || date.month != received_date->month || date.year != received_date->year);
    else { return; }

    date.day = received_date->day;
    date.month = received_date->month;
    date.year = received_date->year;
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
    // Interact with peripheral every 1s
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
    // Interact with peripheral every 1s
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
    // Interact with peripheral every 1s
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

typedef struct CharacterSize {
    uint8_t horizontal_margin;
    uint8_t vertical_margin;
    uint8_t width;
    uint8_t height;
} CharacterSize;

CharacterSize largeCharacterSize = (CharacterSize) { 2, 4, LARGE_ASSET_WIDTH, LARGE_ASSET_HEIGHT };
CharacterSize smallCharacterSize = (CharacterSize) { 1, 2, SMALL_ASSET_WIDTH, SMALL_ASSET_HEIGHT };

void oled_render_character(const char *character, uint8_t x_index, uint8_t y_index, CharacterSize size) {
    uint8_t x_offset = x_index * (size.width + size.horizontal_margin);
    uint8_t y_offset = y_index * (size.height + size.vertical_margin);
        
     for (uint8_t x = 0; x < size.width; x++) {
         for (uint8_t y = 0; y < ceil((float)size.height / 8); y++) {
             uint8_t index = x + (y * size.width);
             for (uint8_t bit = 0; bit < 8; bit++) {
                if (index < size.width * size.height) {
                    oled_write_pixel(x_offset + x, y_offset + y * 8 + bit, character[index] & (1 << bit));
                }
             }
         }
     }
}

const char *digit_small_asset(uint8_t value) {
    switch (value) {
        case 0:     return small0;
        case 1:     return small1;
        case 2:     return small2;
        case 3:     return small3;
        case 4:     return small4;
        case 5:     return small5;
        case 6:     return small6;
        case 7:     return small7;
        case 8:     return small8;
        case 9:     return small9;
        default:    return NULL;
    }
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
        default:    return NULL;
    }
}

void oled_render_number(uint16_t number, uint8_t x_index, uint8_t y_index, uint8_t count, CharacterSize size) {
    uint8_t thousands = floor(number / 1000);
    number -= thousands * 1000;
    uint8_t hundreds = floor(number / 100);
    number -= hundreds * 100;
    uint8_t tens = floor(number / 10);
    number -= tens * 10;
    uint8_t units = number;

    if (count >= 4) {
        oled_render_character(digit_small_asset(thousands), x_index, y_index, size);
        x_index++;
    }
    if (count >= 3) {
        oled_render_character(digit_small_asset(hundreds), x_index, y_index, size);
        x_index++;
    }
    if (count >= 2) {
        oled_render_character(digit_small_asset(tens), x_index, y_index, size);
        x_index++;
    }
    if (count >= 1) {
        oled_render_character(digit_small_asset(units), x_index, y_index, size);
    }
}

void oled_render_time_component(uint8_t component, uint8_t y_index) {
    uint8_t tens = floor(component / 10);
    uint8_t units = component - tens * 10;

    oled_render_character(digit_large_asset(tens), 0, y_index, largeCharacterSize);
    oled_render_character(digit_large_asset(units), 1, y_index, largeCharacterSize);
}

void oled_render_date(uint8_t day, uint8_t month, uint16_t year) {
    oled_render_number(day, 0, 1, 2, smallCharacterSize);
    oled_render_character(smallslash, 2, 1, smallCharacterSize);
    oled_render_number(month, 3, 1, 2, smallCharacterSize);
    oled_render_character(smallslash, 5, 1, smallCharacterSize);
    oled_render_number(year, 6, 1, 4, smallCharacterSize);
}

static uint8_t cpu_y_offset = 48;
static uint8_t cpu_height = 78; // 128 - cpu_y_offset;
static uint8_t cpu_width = 32;

void oled_render_core_usage(uint8_t usage, uint8_t index) {
    uint8_t margin = 1;
    uint8_t core_height = floor(cpu_height / (cpu_usage.count + margin));
    uint8_t core_width = round(usage * cpu_width / 100);

    uint8_t y_offset = cpu_y_offset + index * (core_height + margin);

    for (uint8_t i = 0; i < core_height; i++) {
        for (uint8_t j = 0; j < cpu_width; j++) {
            oled_write_pixel(j, i + y_offset, j < core_width);
        }
    }
}

void oled_render_cpu_usage(void) {
    for (uint8_t i = 0; i < cpu_usage.count; i++) {
        oled_render_core_usage(cpu_usage.cores[i], i);
    }
}

void render_central(void) {
    if (is_locked.value) {
        oled_clear();
        time.changed = true;
        cpu_usage.changed = true;
        return;
    }

    if (time.changed) {
        oled_render_time_component(time.hour, 0);
        oled_render_time_component(time.minute, 1);
        time.changed = false;
    }

    if (cpu_usage.changed) {
        oled_render_cpu_usage();
        cpu_usage.changed = false;
    }
}

void render_peripheral(void) {
    if (is_locked.value) {
        oled_clear();
        host_name.changed = true;
        date.changed = true;
        return;
    }

    if (host_name.changed) {
        oled_write_ln(host_name.value, false);
        host_name.changed = false;
    }

    if (date.changed) {
        oled_render_date(date.day, date.month, date.year);
        date.changed = false;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_central();
    } else {
        render_peripheral();
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

    for (uint8_t i = 0; i < size; i++) {
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
    time.hour = report.data[0];
    time.minute = report.data[1];
    time.changed = true;

    date.day = report.data[2];
    date.month = report.data[3];
    date.year = report.data[5] << 8 | report.data[4]; 
    date.changed = true;
}

void cpu_usage_from_report(Report report) {
    cpu_usage.count = report.size;

    for (uint8_t i = 0; i < cpu_usage.count; i++) {
        cpu_usage.cores[i] = report.data[i];
    }

    cpu_usage.changed = true;
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

