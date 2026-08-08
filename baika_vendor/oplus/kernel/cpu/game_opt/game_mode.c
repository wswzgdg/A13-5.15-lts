// SPDX-License-Identifier: GPL-2.0-only

#include <linux/atomic.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <trace/hooks/sched.h>

#include "game_mode.h"

static BLOCKING_NOTIFIER_HEAD(fengchi_game_mode_chain);
static DEFINE_MUTEX(fengchi_game_mode_lock);
static atomic_t fengchi_game_active = ATOMIC_INIT(0);
static atomic_t fengchi_game_pid = ATOMIC_INIT(-1);
static bool fengchi_auto_switch = true;
static void fengchi_game_exit_workfn(struct work_struct *work);
static DECLARE_WORK(fengchi_game_exit_work, fengchi_game_exit_workfn);

bool fengchi_game_mode_active(void)
{
	return atomic_read(&fengchi_game_active);
}
EXPORT_SYMBOL_GPL(fengchi_game_mode_active);

pid_t fengchi_game_mode_pid(void)
{
	return atomic_read(&fengchi_game_pid);
}
EXPORT_SYMBOL_GPL(fengchi_game_mode_pid);

int fengchi_register_game_mode_notifier(struct notifier_block *notifier)
{
	return blocking_notifier_chain_register(&fengchi_game_mode_chain, notifier);
}
EXPORT_SYMBOL_GPL(fengchi_register_game_mode_notifier);

int fengchi_unregister_game_mode_notifier(struct notifier_block *notifier)
{
	return blocking_notifier_chain_unregister(&fengchi_game_mode_chain, notifier);
}
EXPORT_SYMBOL_GPL(fengchi_unregister_game_mode_notifier);

void fengchi_game_mode_update(bool active, pid_t game_pid)
{
	struct fengchi_game_mode_data data = {
		.game_pid = active ? game_pid : -1,
	};
	bool changed;

	mutex_lock(&fengchi_game_mode_lock);
	changed = fengchi_game_mode_active() != active ||
		fengchi_game_mode_pid() != data.game_pid;
	atomic_set(&fengchi_game_active, active);
	atomic_set(&fengchi_game_pid, data.game_pid);
	if (changed && fengchi_auto_switch)
		blocking_notifier_call_chain(&fengchi_game_mode_chain,
			active ? FENGCHI_GAME_ENTER : FENGCHI_GAME_EXIT, &data);
	mutex_unlock(&fengchi_game_mode_lock);
}
EXPORT_SYMBOL_GPL(fengchi_game_mode_update);

static void fengchi_game_exit_workfn(struct work_struct *work)
{
	fengchi_game_mode_update(false, -1);
}

static void fengchi_free_task(void *unused, struct task_struct *task)
{
	if (task->pid == fengchi_game_mode_pid())
		schedule_work(&fengchi_game_exit_work);
}

static int fengchi_auto_switch_show(struct seq_file *file, void *data)
{
	seq_printf(file, "%d\n", fengchi_auto_switch);
	return 0;
}

static int fengchi_auto_switch_open(struct inode *inode, struct file *file)
{
	return single_open(file, fengchi_auto_switch_show, NULL);
}

static ssize_t fengchi_auto_switch_write(struct file *file,
		const char __user *buffer, size_t count, loff_t *offset)
{
	struct fengchi_game_mode_data data;
	bool enabled;
	int ret;

	ret = kstrtobool_from_user(buffer, count, &enabled);
	if (ret)
		return ret;

	mutex_lock(&fengchi_game_mode_lock);
	if (fengchi_auto_switch != enabled) {
		fengchi_auto_switch = enabled;
		data.game_pid = fengchi_game_mode_pid();
		blocking_notifier_call_chain(&fengchi_game_mode_chain,
			enabled && fengchi_game_mode_active() ?
			FENGCHI_GAME_ENTER : FENGCHI_GAME_EXIT, &data);
	}
	mutex_unlock(&fengchi_game_mode_lock);
	return count;
}

static const struct proc_ops fengchi_auto_switch_ops = {
	.proc_open = fengchi_auto_switch_open,
	.proc_read = seq_read,
	.proc_write = fengchi_auto_switch_write,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

static int fengchi_game_state_show(struct seq_file *file, void *data)
{
	seq_printf(file, "active=%d pid=%d auto_switch=%d\n",
		fengchi_game_mode_active(), fengchi_game_mode_pid(),
		fengchi_auto_switch);
	return 0;
}

static int fengchi_game_state_open(struct inode *inode, struct file *file)
{
	return single_open(file, fengchi_game_state_show, NULL);
}

static const struct proc_ops fengchi_game_state_ops = {
	.proc_open = fengchi_game_state_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

int fengchi_game_mode_init(struct proc_dir_entry *parent)
{
	int ret;

	ret = register_trace_android_vh_free_task(fengchi_free_task, NULL);
	if (ret)
		return ret;
	if (!proc_create("auto_switch", 0664, parent, &fengchi_auto_switch_ops))
		return -ENOMEM;
	if (!proc_create("game_mode_state", 0444, parent, &fengchi_game_state_ops))
		return -ENOMEM;
	return 0;
}

void fengchi_game_mode_exit(void)
{
	unregister_trace_android_vh_free_task(fengchi_free_task, NULL);
	cancel_work_sync(&fengchi_game_exit_work);
	fengchi_game_mode_update(false, -1);
}
