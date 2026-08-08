# SPDX-License-Identifier: GPL-2.0-only

obj-$(CONFIG_OPLUS_FEATURE_GEAS) += oplus_geas_system.o

ccflags-y += -I$(srctree) \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/include \
	-I$(srctree)/../msm-kernel/include \
	-I$(srctree)/../msm-kernel/drivers/soc/qcom/dcvs

oplus_geas_system-y := geas.o

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_FDRIVE)),)
oplus_geas_system-y += geas_frame_drive.o geas_sysctrl.o
endif
ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_BWMON)),)
oplus_geas_system-y += geas_bwmon.o
endif
ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_GPU)),)
oplus_geas_system-y += geas_gpu.o
endif
ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_EMI)),)
oplus_geas_system-y += geas_emi.o
endif
ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_MEMLAT)),)
oplus_geas_system-y += geas_memlat.o
endif
ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_NPU)),)
oplus_geas_system-y += geas_npu.o
endif
