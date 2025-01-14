/*
 * Copyright (c) 2016-2017 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <soc.h>

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_HCI_DRIVER)
#define LOG_MODULE_NAME bt_ctlr_crypto
#include "common/log.h"

#include "hal/ecb.h"

int bt_rand(void *buf, size_t len)
{
	u8_t *buf8 = buf;

	while (len) {
		u32_t v = sys_rand32_get();

		if (len >= sizeof(v)) {
			memcpy(buf8, &v, sizeof(v));

			buf8 += sizeof(v);
			len -= sizeof(v);
		} else {
			memcpy(buf8, &v, len);
			break;
		}
	}

	return 0;
}

int bt_encrypt_le(const u8_t key[16], const u8_t plaintext[16],
		  u8_t enc_data[16])
{
	BT_DBG("key %s", bt_hex(key, 16));
	BT_DBG("plaintext %s", bt_hex(plaintext, 16));

	ecb_encrypt(key, plaintext, enc_data, NULL);

	BT_DBG("enc_data %s", bt_hex(enc_data, 16));

	return 0;
}

int bt_encrypt_be(const u8_t key[16], const u8_t plaintext[16],
		  u8_t enc_data[16])
{
	BT_DBG("key %s", bt_hex(key, 16));
	BT_DBG("plaintext %s", bt_hex(plaintext, 16));

	ecb_encrypt_be(key, plaintext, enc_data);

	BT_DBG("enc_data %s", bt_hex(enc_data, 16));

	return 0;
}
