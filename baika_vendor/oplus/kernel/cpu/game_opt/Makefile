# SPDX-License-Identifier: GPL-2.0-only

obj-$(CONFIG_OPLUS_FEATURE_GAME_OPT) += oplus_game_opt.o

ccflags-y += -I$(srctree) \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/include \
	-I$(srctree)/../msm-kernel/include \
	-I$(srctree)/../msm-kernel/drivers/soc/qcom/dcvs

subdir-ccflags-y += -I$(srctree)/baika_vendor/oplus/kernel/cpu \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/include

oplus_game_opt-y := game_mode.o \
	cpu_load.o \
	cpufreq_limits.o \
	debug.o \
	early_detect.o \
	game_ctrl.o \
	rt_info.o \
	task_load_track.o \
	task_util.o \
	multi_task_util.o \
	multi_rt_info.o \
	yield_opt.o \
	frame_load.o \
	frame_sync.o \
	task_boost/heavy_task_boost.o \
	task_boost/boost_proc.o \
	frame_detect/frame_detect.o \
	oem_data/game_oem_data.o \
	critical_task_boost.o \
	geas_ctrl.o \
	hybrid_frame_sync.o \
	game_sysctl.o \
	rwsem_opt.o

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_CPU)),)
oplus_game_opt-y += geas_assist.o
endif
