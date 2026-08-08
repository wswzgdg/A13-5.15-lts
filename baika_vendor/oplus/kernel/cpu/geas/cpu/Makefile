# SPDX-License-Identifier: GPL-2.0-only

obj-$(CONFIG_OPLUS_FEATURE_GEAS_CPU) += oplus_geas_cpu.o

ccflags-y += -I$(srctree) \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/game_opt \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/include

oplus_geas_cpu-y := geas_cpu.o \
	geas_cpu_para.o \
	geas_cpu_sysctrl.o \
	geas_debug.o \
	geas_dyn_em.o \
	geas_task_manager.o \
	pipline_eas.o \
	sharebuck.o
