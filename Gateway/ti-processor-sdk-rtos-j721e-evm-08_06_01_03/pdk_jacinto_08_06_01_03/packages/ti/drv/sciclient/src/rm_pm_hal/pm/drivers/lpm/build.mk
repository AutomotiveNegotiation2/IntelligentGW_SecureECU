
cppflags-y += -I$(srctree)/rm_pm_hal/pm/drivers/lpm/soc/$(TARGET_SOC)/

obj-y += lpm_handler.o padcfg.o rtc.o gtc.o

obj-$(CONFIG_LPM_INCLUDE_OSAL) += osal/
