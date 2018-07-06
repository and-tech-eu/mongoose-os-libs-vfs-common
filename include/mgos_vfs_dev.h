/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_FW_SRC_MGOS_VFS_DEV_H_
#define CS_FW_SRC_MGOS_VFS_DEV_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mgos_vfs_dev {
  const struct mgos_vfs_dev_ops *ops;
  void *dev_data;
  int refs;
};

enum mgos_vfs_dev_err {
  MGOS_VFS_DEV_ERR_NONE = 0,
  MGOS_VFS_DEV_ERR_INVAL = -1,    /* Invalid parameter. */
  MGOS_VFS_DEV_ERR_NOMEM = -2,    /* Not enough memory. */
  MGOS_VFS_DEV_ERR_NOSPC = -3,    /* Not enough space on device. */
  MGOS_VFS_DEV_ERR_ACCESS = -4,   /* Access denied. */
  MGOS_VFS_DEV_ERR_TIMEDOUT = -5, /* Timeout. */
  MGOS_VFS_DEV_ERR_CORRUPT = -6,  /* Integrity error (CRC, ECC or checksum). */
  MGOS_VFS_DEV_ERR_NXIO = -7,     /* Device went away. */
  MGOS_VFS_DEV_ERR_IO = -8,       /* Some other kind of I/O error. */
};

struct mgos_vfs_dev_ops {
  enum mgos_vfs_dev_err (*open)(struct mgos_vfs_dev *dev, const char *opts);
  /* Note: read and write should return 0 if ok or an error code,
   * do not return positive values, it's all or nothing. */
  enum mgos_vfs_dev_err (*read)(struct mgos_vfs_dev *dev, size_t offset,
                                size_t len, void *dst);
  enum mgos_vfs_dev_err (*write)(struct mgos_vfs_dev *dev, size_t offset,
                                 size_t len, const void *src);
  enum mgos_vfs_dev_err (*erase)(struct mgos_vfs_dev *dev, size_t offset,
                                 size_t len);
  size_t (*get_size)(struct mgos_vfs_dev *dev);
  enum mgos_vfs_dev_err (*close)(struct mgos_vfs_dev *dev);
};

bool mgos_vfs_dev_register_type(const char *name,
                                const struct mgos_vfs_dev_ops *ops);

struct mgos_vfs_dev *mgos_vfs_dev_open(const char *name, const char *opts);

bool mgos_vfs_dev_close(struct mgos_vfs_dev *dev);

#ifdef __cplusplus
}
#endif

#endif /* CS_FW_SRC_MGOS_VFS_DEV_H_ */