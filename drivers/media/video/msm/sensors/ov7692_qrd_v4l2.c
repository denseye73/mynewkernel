/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "msm_sensor.h"
#define SENSOR_NAME "ov7692"
#define PLATFORM_DRIVER_NAME "msm_camera_ov7692"
#define ov7692_obj ov7692_##obj
#define MSB                             1
#define LSB                             0

DEFINE_MUTEX(ov7692_mut);
static struct msm_sensor_ctrl_t ov7692_s_ctrl;

static struct msm_camera_i2c_reg_conf ov7692_prev_settings[] = {
	{0x12, 0x80},
	{0x0e, 0x08},
	{0x69, 0x52},
	{0x1e, 0xb3},
	{0x48, 0x42},
	{0xff, 0x01},
	{0xae, 0xa0},
	{0xa8, 0x26},
	{0xb4, 0xc0},
	{0xb5, 0x40},
	{0xff, 0x00},
	{0x0c, 0x00},
	{0x62, 0x10},
	{0x12, 0x00},
	{0x17, 0x65},
	{0x18, 0xa4},
	{0x19, 0x0a},
	{0x1a, 0xf6},
	{0x3e, 0x30},
	{0x64, 0x0a},
	{0xff, 0x01},
	{0xb4, 0xc0},
	{0xff, 0x00},
	{0x67, 0x20},
	{0x81, 0x3f},
	{0xcc, 0x02},
	{0xcd, 0x80},
	{0xce, 0x01},
	{0xcf, 0xe0},
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xd0, 0x48},
	{0x82, 0x03},
	{0x70, 0x00},
	{0x71, 0x34},
	{0x74, 0x28},
	{0x75, 0x98},
	{0x76, 0x00},
	{0x77, 0x64},
	{0x78, 0x01},
	{0x79, 0xc2},
	{0x7a, 0x4e},
	{0x7b, 0x1f},
	{0x7c, 0x00},
	{0x11, 0x00},
	{0x20, 0x00},
	{0x21, 0x23},
	{0x50, 0x9a},
	{0x51, 0x80},
	{0x4c, 0x7d},
	{0x85, 0x10},
	{0x86, 0x00},
	{0x87, 0x00},
	{0x88, 0x00},
	{0x89, 0x2a},
	{0x8a, 0x26},
	{0x8b, 0x22},
	{0xbb, 0x7a},
	{0xbc, 0x69},
	{0xbd, 0x11},
	{0xbe, 0x13},
	{0xbf, 0x81},
	{0xc0, 0x96},
	{0xc1, 0x1e},
	{0xb7, 0x05},
	{0xb8, 0x09},
	{0xb9, 0x00},
	{0xba, 0x18},
	{0x5a, 0x1f},
	{0x5b, 0x9f},
	{0x5c, 0x6a},
	{0x5d, 0x42},
	{0x24, 0x78},
	{0x25, 0x68},
	{0x26, 0xb3},
	{0xa3, 0x0b},
	{0xa4, 0x15},
	{0xa5, 0x2a},
	{0xa6, 0x51},
	{0xa7, 0x63},
	{0xa8, 0x74},
	{0xa9, 0x83},
	{0xaa, 0x91},
	{0xab, 0x9e},
	{0xac, 0xaa},
	{0xad, 0xbe},
	{0xae, 0xce},
	{0xaf, 0xe5},
	{0xb0, 0xf3},
	{0xb1, 0xfb},
	{0xb2, 0x06},
	{0x8c, 0x5c},
	{0x8d, 0x11},
	{0x8e, 0x12},
	{0x8f, 0x19},
	{0x90, 0x50},
	{0x91, 0x20},
	{0x92, 0x96},
	{0x93, 0x80},
	{0x94, 0x13},
	{0x95, 0x1b},
	{0x96, 0xff},
	{0x97, 0x00},
	{0x98, 0x3d},
	{0x99, 0x36},
	{0x9a, 0x51},
	{0x9b, 0x43},
	{0x9c, 0xf0},
	{0x9d, 0xf0},
	{0x9e, 0xf0},
	{0x9f, 0xff},
	{0xa0, 0x68},
	{0xa1, 0x62},
	{0xa2, 0x0e},

};

static struct msm_camera_i2c_reg_conf ov7692_snap_settings[] = {
	{0x12, 0x80},
	{0x0e, 0x08},
	{0x69, 0x52},
	{0x1e, 0xb3},
	{0x48, 0x42},
	{0xff, 0x01},
	{0xae, 0xa0},
	{0xa8, 0x26},
	{0xb4, 0xc0},
	{0xb5, 0x40},
	{0xff, 0x00},
	{0x0c, 0x00},
	{0x62, 0x10},
	{0x12, 0x00},
	{0x17, 0x65},
	{0x18, 0xa4},
	{0x19, 0x0a},
	{0x1a, 0xf6},
	{0x3e, 0x30},
	{0x64, 0x0a},
	{0xff, 0x01},
	{0xb4, 0xc0},
	{0xff, 0x00},
	{0x67, 0x20},
	{0x81, 0x3f},
	{0xcc, 0x02},
	{0xcd, 0x80},
	{0xce, 0x01},
	{0xcf, 0xe0},
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xd0, 0x48},
	{0x82, 0x03},
	{0x70, 0x00},
	{0x71, 0x34},
	{0x74, 0x28},
	{0x75, 0x98},
	{0x76, 0x00},
	{0x77, 0x64},
	{0x78, 0x01},
	{0x79, 0xc2},
	{0x7a, 0x4e},
	{0x7b, 0x1f},
	{0x7c, 0x00},
	{0x11, 0x00},
	{0x20, 0x00},
	{0x21, 0x23},
	{0x50, 0x9a},
	{0x51, 0x80},
	{0x4c, 0x7d},
	{0x85, 0x10},
	{0x86, 0x00},
	{0x87, 0x00},
	{0x88, 0x00},
	{0x89, 0x2a},
	{0x8a, 0x26},
	{0x8b, 0x22},
	{0xbb, 0x7a},
	{0xbc, 0x69},
	{0xbd, 0x11},
	{0xbe, 0x13},
	{0xbf, 0x81},
	{0xc0, 0x96},
	{0xc1, 0x1e},
	{0xb7, 0x05},
	{0xb8, 0x09},
	{0xb9, 0x00},
	{0xba, 0x18},
	{0x5a, 0x1f},
	{0x5b, 0x9f},
	{0x5c, 0x6a},
	{0x5d, 0x42},
	{0x24, 0x78},
	{0x25, 0x68},
	{0x26, 0xb3},
	{0xa3, 0x0b},
	{0xa4, 0x15},
	{0xa5, 0x2a},
	{0xa6, 0x51},
	{0xa7, 0x63},
	{0xa8, 0x74},
	{0xa9, 0x83},
	{0xaa, 0x91},
	{0xab, 0x9e},
	{0xac, 0xaa},
	{0xad, 0xbe},
	{0xae, 0xce},
	{0xaf, 0xe5},
	{0xb0, 0xf3},
	{0xb1, 0xfb},
	{0xb2, 0x06},
	{0x8c, 0x5c},
	{0x8d, 0x11},
	{0x8e, 0x12},
	{0x8f, 0x19},
	{0x90, 0x50},
	{0x91, 0x20},
	{0x92, 0x96},
	{0x93, 0x80},
	{0x94, 0x13},
	{0x95, 0x1b},
	{0x96, 0xff},
	{0x97, 0x00},
	{0x98, 0x3d},
	{0x99, 0x36},
	{0x9a, 0x51},
	{0x9b, 0x43},
	{0x9c, 0xf0},
	{0x9d, 0xf0},
	{0x9e, 0xf0},
	{0x9f, 0xff},
	{0xa0, 0x68},
	{0xa1, 0x62},
	{0xa2, 0x0e},

};

static struct msm_camera_i2c_reg_conf ov7692_recommend_settings[] = {
	{0x12, 0x80},
	{0x0e, 0x08},
	{0x69, 0x52},
	{0x1e, 0xb3},
	{0x48, 0x42},
	{0xff, 0x01},
	{0xae, 0xa0},
	{0xa8, 0x26},
	{0xb4, 0xc0},
	{0xb5, 0x40},
	{0xff, 0x00},
	{0x0c, 0x00},
	{0x62, 0x10},
	{0x12, 0x00},
	{0x17, 0x65},
	{0x18, 0xa4},
	{0x19, 0x0a},
	{0x1a, 0xf6},
	{0x3e, 0x30},
	{0x64, 0x0a},
	{0xff, 0x01},
	{0xb4, 0xc0},
	{0xff, 0x00},
	{0x67, 0x20},
	{0x81, 0x3f},
	{0xcc, 0x02},
	{0xcd, 0x80},
	{0xce, 0x01},
	{0xcf, 0xe0},
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xd0, 0x48},
	{0x82, 0x03},
	{0x70, 0x00},
	{0x71, 0x34},
	{0x74, 0x28},
	{0x75, 0x98},
	{0x76, 0x00},
	{0x77, 0x64},
	{0x78, 0x01},
	{0x79, 0xc2},
	{0x7a, 0x4e},
	{0x7b, 0x1f},
	{0x7c, 0x00},
	{0x11, 0x00},
	{0x20, 0x00},
	{0x21, 0x23},
	{0x50, 0x9a},
	{0x51, 0x80},
	{0x4c, 0x7d},
	{0x85, 0x10},
	{0x86, 0x00},
	{0x87, 0x00},
	{0x88, 0x00},
	{0x89, 0x2a},
	{0x8a, 0x26},
	{0x8b, 0x22},
	{0xbb, 0x7a},
	{0xbc, 0x69},
	{0xbd, 0x11},
	{0xbe, 0x13},
	{0xbf, 0x81},
	{0xc0, 0x96},
	{0xc1, 0x1e},
	{0xb7, 0x05},
	{0xb8, 0x09},
	{0xb9, 0x00},
	{0xba, 0x18},
	{0x5a, 0x1f},
	{0x5b, 0x9f},
	{0x5c, 0x6a},
	{0x5d, 0x42},
	{0x24, 0x78},
	{0x25, 0x68},
	{0x26, 0xb3},
	{0xa3, 0x0b},
	{0xa4, 0x15},
	{0xa5, 0x2a},
	{0xa6, 0x51},
	{0xa7, 0x63},
	{0xa8, 0x74},
	{0xa9, 0x83},
	{0xaa, 0x91},
	{0xab, 0x9e},
	{0xac, 0xaa},
	{0xad, 0xbe},
	{0xae, 0xce},
	{0xaf, 0xe5},
	{0xb0, 0xf3},
	{0xb1, 0xfb},
	{0xb2, 0x06},
	{0x8c, 0x5c},
	{0x8d, 0x11},
	{0x8e, 0x12},
	{0x8f, 0x19},
	{0x90, 0x50},
	{0x91, 0x20},
	{0x92, 0x96},
	{0x93, 0x80},
	{0x94, 0x13},
	{0x95, 0x1b},
	{0x96, 0xff},
	{0x97, 0x00},
	{0x98, 0x3d},
	{0x99, 0x36},
	{0x9a, 0x51},
	{0x9b, 0x43},
	{0x9c, 0xf0},
	{0x9d, 0xf0},
	{0x9e, 0xf0},
	{0x9f, 0xff},
	{0xa0, 0x68},
	{0xa1, 0x62},
	{0xa2, 0x0e},

};

static struct v4l2_subdev_info ov7692_subdev_info[] = {
	{
		.code   = V4L2_MBUS_FMT_YUYV8_2X8,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.fmt    = 1,
		.order    = 0,
	},
	/* more can be supported, to be added later */
};


static struct msm_camera_i2c_conf_array ov7692_init_conf[] = {
	{&ov7692_recommend_settings[0],
	ARRAY_SIZE(ov7692_recommend_settings), 0, MSM_CAMERA_I2C_BYTE_DATA}
};

static struct msm_camera_i2c_conf_array ov7692_confs[] = {
	{&ov7692_snap_settings[0],
	ARRAY_SIZE(ov7692_snap_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
	{&ov7692_prev_settings[0],
	ARRAY_SIZE(ov7692_prev_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
};

static struct msm_sensor_output_info_t ov7692_dimensions[] = {
	{
		.x_output = 0x280,
		.y_output = 0x1E0,
		.line_length_pclk = 0x290,
		.frame_length_lines = 0x1EC,
		.vt_pixel_clk = 9216000,
		.op_pixel_clk = 9216000,
		.binning_factor = 1,
	},
	{
		.x_output = 0x280,
		.y_output = 0x1E0,
		.line_length_pclk = 0x290,
		.frame_length_lines = 0x1EC,
		.vt_pixel_clk = 9216000,
		.op_pixel_clk = 9216000,
		.binning_factor = 1,
	},
};


static struct msm_camera_csi_params ov7692_csi_params = {
	.data_format = CSI_8BIT,
	.lane_cnt    = 1,
	.lane_assign = 0xe4,
	.dpcm_scheme = 0,
	.settle_cnt  = 0x14,
};

static struct msm_camera_csi_params *ov7692_csi_params_array[] = {
	&ov7692_csi_params,
	&ov7692_csi_params,
};

static struct msm_sensor_output_reg_addr_t ov7692_reg_addr = {
	.x_output = 0xCC,
	.y_output = 0xCE,
	.line_length_pclk = 0xC8,
	.frame_length_lines = 0xCA,
};

static struct msm_sensor_id_info_t ov7692_id_info = {
	.sensor_id_reg_addr = 0x0A,
	.sensor_id = 0x7692,
};

static struct msm_sensor_exp_gain_info_t ov7692_exp_gain_info = {
	.coarse_int_time_addr = 0x0202,
	.global_gain_addr = 0x0204,
	.vert_offset = 4,
};

static inline uint8_t ov7692_byte(uint16_t word, uint8_t offset)
{
	return word >> (offset * BITS_PER_BYTE);
}


static const struct i2c_device_id ov7692_i2c_id[] = {
	{SENSOR_NAME, (kernel_ulong_t)&ov7692_s_ctrl},
	{ }
};
static int ov7692_pwdn_gpio;
static int ov7692_reset_gpio;

static int ov7692_probe_init_gpio(const struct msm_camera_sensor_info *data)
{
	int rc = 0;
	CDBG("%s: entered\n", __func__);

	ov7692_pwdn_gpio = data->sensor_pwd;
	ov7692_reset_gpio = data->sensor_reset ;

	CDBG("%s: pwdn_gpio:%d, reset_gpio:%d\n", __func__,
			ov7692_pwdn_gpio, ov7692_reset_gpio);

	if (data->sensor_reset_enable)
		gpio_direction_output(data->sensor_reset, 1);

	gpio_direction_output(data->sensor_pwd, 1);

	return rc;

}
static void ov7692_power_on(void)
{
	CDBG("%s\n", __func__);
	gpio_set_value(ov7692_pwdn_gpio, 0);
}

static void ov7692_power_down(void)
{
	CDBG("%s\n", __func__);
	gpio_set_value(ov7692_pwdn_gpio, 1);
}

int32_t ov7692_sensor_i2c_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	int32_t rc = 0;
	struct msm_sensor_ctrl_t *s_ctrl;
	rc = msm_sensor_i2c_probe(client, id);

	ov7692_power_down();

	if (client->dev.platform_data == NULL) {
		pr_err("%s: NULL sensor data\n", __func__);
		return -EFAULT;
	}

	s_ctrl = client->dev.platform_data;
	if (s_ctrl->sensordata->pmic_gpio_enable)
		lcd_camera_power_onoff(0);

	return rc;

}

static struct i2c_driver ov7692_i2c_driver = {
	.id_table = ov7692_i2c_id,
	.probe  = msm_sensor_i2c_probe,
	.driver = {
		.name = SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client ov7692_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
};

static int __init msm_sensor_init_module(void)
{
	int rc = 0;
	CDBG("OV7692\n");

	rc = i2c_add_driver(&ov7692_i2c_driver);

	return rc;
}

static struct v4l2_subdev_core_ops ov7692_subdev_core_ops = {
	.ioctl = msm_sensor_subdev_ioctl,
	.s_power = msm_sensor_power,
};

static struct v4l2_subdev_video_ops ov7692_subdev_video_ops = {
	.enum_mbus_fmt = msm_sensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops ov7692_subdev_ops = {
	.core = &ov7692_subdev_core_ops,
	.video  = &ov7692_subdev_video_ops,
};

static int32_t ov7692_i2c_txdata(struct i2c_client *ov7692_client,
		unsigned short saddr,
		unsigned char *txdata, int length)
{
	struct i2c_msg msg[] = {
		{
			.addr = saddr,
			.flags = 0,
			.len = 2,
			.buf = txdata,
		},
	};
	if (i2c_transfer(ov7692_client->adapter, msg, 1) < 0) {
		CDBG("ov7692_i2c_txdata faild 0x%x\n", ov7692_client->addr);
		return -EIO;
	}

	return 0;
}
static int32_t ov7692_i2c_write_b_sensor(struct i2c_client *ov7692_client,
		uint8_t waddr,
		uint8_t bdata)
{
	int32_t rc = -EFAULT;
	unsigned char buf[2];

	memset(buf, 0, sizeof(buf));
	buf[0] = waddr;
	buf[1] = bdata;
	CDBG("i2c_write_b addr = 0x%x, val = 0x%x\n", waddr, bdata);
	rc = ov7692_i2c_txdata(ov7692_client, ov7692_client->addr >> 1, buf, 2);
	if (rc < 0)
		CDBG("i2c_write_b failed, addr = 0x%x, val = 0x%x!\n",
		waddr, bdata);

	return rc;
}

static void ov7692_sw_reset(struct msm_sensor_ctrl_t *s_ctrl)
{

	CDBG("%s\n", __func__);
	ov7692_i2c_write_b_sensor(s_ctrl->sensor_i2c_client->client,
			0x12, 0x80);
}

static void ov7692_hw_reset(void)
{
	CDBG("--CAMERA-- %s ... (Start...)\n", __func__);
	gpio_set_value(ov7692_reset_gpio, 1);   /*reset camera reset pin*/
	usleep_range(5000, 5100);
	gpio_set_value(ov7692_reset_gpio, 0);
	usleep_range(5000, 5100);
	gpio_set_value(ov7692_reset_gpio, 1);
	usleep_range(1000, 1100);
	CDBG("--CAMERA-- %s ... (End...)\n", __func__);
}



int32_t ov7692_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	struct msm_camera_sensor_info *info = NULL;

	CDBG("%s: %d\n", __func__, __LINE__);

	rc = msm_sensor_power_up(s_ctrl);
	if (rc < 0) {
		CDBG("%s: msm_sensor_power_up failed\n", __func__);
		return rc;
	}
	info = s_ctrl->sensordata;

	rc = ov7692_probe_init_gpio(info);
	if (rc < 0) {
		CDBG("%s: gpio init failed\n", __func__);
		goto power_up_fail;
	}
	/* turn on LDO for PVT */
	if (info->pmic_gpio_enable)
		lcd_camera_power_onoff(1);

	ov7692_power_down();

	usleep_range(5000, 5100);

	ov7692_power_on();
	usleep_range(5000, 5100);

	if (info->sensor_reset_enable)
		ov7692_hw_reset();
	else
		ov7692_sw_reset(s_ctrl);

	return rc;

power_up_fail:
	CDBG("ov7692_sensor_power_up: OV7692 SENSOR POWER UP FAILS!\n");
	if (info->pmic_gpio_enable)
		lcd_camera_power_onoff(0);
	return rc;


}


static struct msm_sensor_fn_t ov7692_func_tbl = {
	.sensor_start_stream = msm_sensor_start_stream,
	.sensor_stop_stream = msm_sensor_stop_stream,
	.sensor_group_hold_on = msm_sensor_group_hold_on,
	.sensor_group_hold_off = msm_sensor_group_hold_off,
	.sensor_set_fps = msm_sensor_set_fps,
	.sensor_setting = msm_sensor_setting3,
	.sensor_set_sensor_mode = msm_sensor_set_sensor_mode,
	.sensor_mode_init = msm_sensor_mode_init,
	.sensor_get_output_info = msm_sensor_get_output_info,
	.sensor_config = msm_sensor_config,
	.sensor_power_up = ov7692_sensor_power_up,
	.sensor_power_down = msm_sensor_power_down,
};

static struct msm_sensor_reg_t ov7692_regs = {
	.default_data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.start_stream_conf_size = 0,
	.stop_stream_conf_size = 0,
	.group_hold_on_conf_size = 0,
	.group_hold_off_conf_size = 0,
	.init_settings = &ov7692_init_conf[0],
	.init_size = ARRAY_SIZE(ov7692_init_conf),
	.mode_settings = &ov7692_confs[0],
	.output_settings = &ov7692_dimensions[0],
	.num_conf = ARRAY_SIZE(ov7692_confs),
};

static struct msm_sensor_ctrl_t ov7692_s_ctrl = {
	.msm_sensor_reg = &ov7692_regs,
	.sensor_i2c_client = &ov7692_sensor_i2c_client,
	.sensor_i2c_addr = 0x78,
	.sensor_output_reg_addr = &ov7692_reg_addr,
	.sensor_id_info = &ov7692_id_info,
	.sensor_exp_gain_info = &ov7692_exp_gain_info,
	.cam_mode = MSM_SENSOR_MODE_INVALID,
	.csic_params = &ov7692_csi_params_array[0],
	.msm_sensor_mutex = &ov7692_mut,
	.sensor_i2c_driver = &ov7692_i2c_driver,
	.sensor_v4l2_subdev_info = ov7692_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(ov7692_subdev_info),
	.sensor_v4l2_subdev_ops = &ov7692_subdev_ops,
	.func_tbl = &ov7692_func_tbl,
	.clk_rate = MSM_SENSOR_MCLK_24HZ,
};

module_init(msm_sensor_init_module);
MODULE_DESCRIPTION("Omni VGA YUV sensor driver");
MODULE_LICENSE("GPL v2");
