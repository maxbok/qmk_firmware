CONVERT_TO = elite_pi
RAW_ENABLE = yes

BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif

