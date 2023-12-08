CONVERT_TO = elite_pi
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RAW_ENABLE = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif

