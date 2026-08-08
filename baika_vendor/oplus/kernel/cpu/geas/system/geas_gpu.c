/*
 * a simple kernel module: powermodel_proc
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/geas_ctrl.h>
#include "geas.h"

static struct gpu_params gpu_data;

static int geas_update_gpu_params(struct gpu_params *gpu_data)
{
	return -EOPNOTSUPP;
}

extern int (*game_update_geas_gpu_params)(struct gpu_params * gpu_data);

int update_gpu_params(struct gpu_params * data)
{
	static DEFINE_MUTEX(update_gpu_params_lock);
	int ret;

	mutex_lock(&update_gpu_params_lock);

	if (data == NULL) {
		pr_err("%s, null data", __func__);
		mutex_unlock(&update_gpu_params_lock);
		return -1;
	}
	memcpy(&gpu_data, data, sizeof(struct gpu_params));
	ret = geas_update_gpu_params(&gpu_data);
	if (ret) {
		mutex_unlock(&update_gpu_params_lock);
		return ret;
	}

	pr_err("%s, imin = %d, imax = %d, amin = %d, amax = %d", __func__, data->imin, data->imax, data->amin, data->amax);

	mutex_unlock(&update_gpu_params_lock);

	return 0;
}

int geas_gpu_init(void)
{
	game_update_geas_gpu_params = update_gpu_params;

	pr_err("%s", __func__);
	return 0;
}

void geas_gpu_exit(void)
{

}
