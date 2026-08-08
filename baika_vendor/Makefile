obj-$(CONFIG_OPLUS_FEATURE_GAME_OPT) += oplus_game_opt.o
obj-$(CONFIG_OPLUS_FEATURE_GEAS_CPU) += oplus_geas_cpu.o
obj-$(CONFIG_OPLUS_FEATURE_GEAS) += oplus_geas_system.o

ccflags-y += -I$(srctree) \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/game_opt \
	-I$(srctree)/baika_vendor/oplus/kernel/cpu/include \
	-I$(srctree)/../msm-kernel/include \
	-I$(srctree)/../msm-kernel/drivers/soc/qcom/dcvs \
	-Wno-declaration-after-statement \
	-Wno-gcc-compat \
	-Wno-unused-function \
	-Wno-unused-variable

oplus_game_opt-y := \
	oplus/kernel/cpu/game_opt/game_mode.o \
	oplus/kernel/cpu/game_opt/cpu_load.o \
	oplus/kernel/cpu/game_opt/cpufreq_limits.o \
	oplus/kernel/cpu/game_opt/debug.o \
	oplus/kernel/cpu/game_opt/early_detect.o \
	oplus/kernel/cpu/game_opt/game_ctrl.o \
	oplus/kernel/cpu/game_opt/rt_info.o \
	oplus/kernel/cpu/game_opt/task_load_track.o \
	oplus/kernel/cpu/game_opt/task_util.o \
	oplus/kernel/cpu/game_opt/multi_task_util.o \
	oplus/kernel/cpu/game_opt/multi_rt_info.o \
	oplus/kernel/cpu/game_opt/yield_opt.o \
	oplus/kernel/cpu/game_opt/frame_load.o \
	oplus/kernel/cpu/game_opt/frame_sync.o \
	oplus/kernel/cpu/game_opt/task_boost/heavy_task_boost.o \
	oplus/kernel/cpu/game_opt/task_boost/boost_proc.o \
	oplus/kernel/cpu/game_opt/frame_detect/frame_detect.o \
	oplus/kernel/cpu/game_opt/oem_data/game_oem_data.o \
	oplus/kernel/cpu/game_opt/critical_task_boost.o \
	oplus/kernel/cpu/game_opt/geas_ctrl.o \
	oplus/kernel/cpu/game_opt/geas_assist.o \
	oplus/kernel/cpu/game_opt/hybrid_frame_sync.o \
	oplus/kernel/cpu/game_opt/game_sysctl.o \
	oplus/kernel/cpu/game_opt/rwsem_opt.o

oplus_geas_cpu-y := \
	oplus/kernel/cpu/geas/cpu/geas_cpu.o \
	oplus/kernel/cpu/geas/cpu/geas_cpu_para.o \
	oplus/kernel/cpu/geas/cpu/geas_cpu_sysctrl.o \
	oplus/kernel/cpu/geas/cpu/geas_debug.o \
	oplus/kernel/cpu/geas/cpu/geas_dyn_em.o \
	oplus/kernel/cpu/geas/cpu/geas_task_manager.o \
	oplus/kernel/cpu/geas/cpu/pipline_eas.o \
	oplus/kernel/cpu/geas/cpu/sharebuck.o

oplus_geas_system-y := oplus/kernel/cpu/geas/system/geas.o

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_FDRIVE)),)
oplus_geas_system-y += \
	oplus/kernel/cpu/geas/system/geas_frame_drive.o \
	oplus/kernel/cpu/geas/system/geas_sysctrl.o
endif

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_BWMON)),)
oplus_geas_system-y += oplus/kernel/cpu/geas/system/geas_bwmon.o
endif

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_GPU)),)
oplus_geas_system-y += oplus/kernel/cpu/geas/system/geas_gpu.o
endif

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_EMI)),)
oplus_geas_system-y += oplus/kernel/cpu/geas/system/geas_emi.o
endif

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_MEMLAT)),)
oplus_geas_system-y += oplus/kernel/cpu/geas/system/geas_memlat.o
endif

ifneq ($(filter y m,$(CONFIG_OPLUS_FEATURE_GEAS_NPU)),)
oplus_geas_system-y += oplus/kernel/cpu/geas/system/geas_npu.o
endif
