/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _OPLUS_FENGCHI_GAME_MODE_H
#define _OPLUS_FENGCHI_GAME_MODE_H

#include <linux/notifier.h>
#include <linux/types.h>

enum fengchi_game_mode_event {
	FENGCHI_GAME_EXIT = 0,
	FENGCHI_GAME_ENTER = 1,
};

struct fengchi_game_mode_data {
	pid_t game_pid;
};

int fengchi_game_mode_init(struct proc_dir_entry *parent);
void fengchi_game_mode_exit(void);
void fengchi_game_mode_update(bool active, pid_t game_pid);
bool fengchi_game_mode_active(void);
pid_t fengchi_game_mode_pid(void);
int fengchi_register_game_mode_notifier(struct notifier_block *notifier);
int fengchi_unregister_game_mode_notifier(struct notifier_block *notifier);

#endif
