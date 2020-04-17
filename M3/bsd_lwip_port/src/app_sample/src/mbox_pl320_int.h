/** @file
 *
 * @brief GOAL ARM PL320 Mailbox Driver - Internal Header
 *
 * @copyright
 * Copyright 2010-2017.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef MBOX_PL320_INT_H
#define MBOX_PL320_INT_H


/****************************************************************************/
/* Register Table */
/****************************************************************************/

/**< register table - http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0306b/CHDBBEFB.html */

#define GOAL_DRV_MBOX_PL320_RV_LIST \
    /* GOAL_DRV_MBOX_PL320_RV(addrReg, nameReg,                                 , shfVal, mskVal, ofsSub, ofsNext  flgReg */         \
    GOAL_DRV_MBOX_PL320_RV(0x0000, GOAL_DRV_MBOX_PL320_REG_IPCMXSOURCE          ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_RW  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0004, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_SET        ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_WO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0008, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_CLR        ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_WO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x000C, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_STATUS     ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_RO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0010, GOAL_DRV_MBOX_PL320_REG_IPCMX_MODE_AUTO_ACK  ,  0, 0x00000001,   0,    0x40,    GOAL_REG_FLG_RW  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0010, GOAL_DRV_MBOX_PL320_REG_IPCMX_MODE_AUTO_LINK ,  1, 0x00000001,   0,    0x40,    GOAL_REG_FLG_RW  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0014, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_SET        ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_WO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0018, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_CLEAR      ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_WO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x001C, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_STATUS     ,  0, 0x00000007,   0,    0x40,    GOAL_REG_FLG_RO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0020, GOAL_DRV_MBOX_PL320_REG_IPCMXSEND            ,  0, 0x00000003,   0,    0x40,    GOAL_REG_FLG_RW  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0024, GOAL_DRV_MBOX_PL320_REG_DATA                 ,  0, UINT32_MAX,   4,    0x40,    GOAL_REG_FLG_RW  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0800, GOAL_DRV_MBOX_PL320_REG_IPCMX_INT_MSK_STATUS ,  0, 0x00000007,   0,    0x08,    GOAL_REG_FLG_RO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0804, GOAL_DRV_MBOX_PL320_REG_IPCMX_INT_RAW_STATUS ,  0, 0x00000007,   0,    0x08,    GOAL_REG_FLG_RO  ),  \
    GOAL_DRV_MBOX_PL320_RV(0x0900, GOAL_DRV_MBOX_PL320_REG_IPCM_CONFIG_STATUS   ,  0, 0x003F3F07,   0,    0x08,    GOAL_REG_FLG_RO  )


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_DRV_MBOX_PL320_DATA_REG_MAX    7   /**< max count of data registers */
#define GOAL_DRV_MBOX_PL320_IPCMXSOURCE_NOT_SET 0 /**< source not set */
#define GOAL_DRV_MBOX_PL320_IPCMXDESTINATION_NOT_SET 0 /**< source not set */
#define GOAL_DRV_MBOX_PL320_IPCMXSEND_SEND_INACTIVE 0 /**< mailbox idle */
#define GOAL_DRV_MBOX_PL320_IPCMXSEND_SEND_DEST 1 /**< send message to destination */

/* register masks */
#define GOAL_DRV_MBOX_PL320_DFLT_MSK_3_BIT 0x07 /**< default mask mailbox registers */
#define GOAL_DRV_MBOX_PL320_SOURCE_0  (1 << 0)  /**< 1st legal one-hot encoded source id */
#define GOAL_DRV_MBOX_PL320_SOURCE_1  (1 << 1)  /**< 2nd legal one-hot encoded source id */
#define GOAL_DRV_MBOX_PL320_SOURCE_2  (1 << 2)  /**< 3rd legal one-hot encoded source id */

/* Timeout */
#ifndef GOAL_DRV_MBOX_PL320_TIMEOUT_MS
#  define GOAL_DRV_MBOX_PL320_TIMEOUT_MS   5    /**< Deadline time offset in ms */
#endif


/****************************************************************************/
/* Structures */
/****************************************************************************/

/**< PL320 description and data buffer */
typedef struct GOAL_DRV_MBOX_PL320_T {
    struct GOAL_DRV_MBOX_PL320_T *pNext;        /**< next list element */
    GOAL_MA_MBOX_T *pMaMbox;                    /**< mailbox MA handle */
    uint8_t *pAddrBase;                         /**< register base address */
    uint32_t idEvent;                           /**< list entry id */
    unsigned int idMbox;                        /**< own mailbox ID */
    unsigned int idMboxForeign;                 /**< foreign mailbox ID */
    unsigned int cntDataReg;                    /**< count of data registers */
    GOALDRV_MBOX_PL320_CFG_T cfg;               /**< configuration of transmission/ receive */
    uint32_t valTmp[GOAL_DRV_MBOX_PL320_DATA_REG_MAX]; /**< temporary value storage */
} GOAL_DRV_MBOX_PL320_T;


/**< PL320 register value information */
typedef struct {
    unsigned int addrReg;                       /**< register address */
    unsigned int valShift;                      /**< value shift */
    unsigned int valMask;                       /**< value mask */
    unsigned int ofsSub;                        /**< sub-index offset */
    unsigned int ofsNext;                       /**< next entry offset */
    unsigned int flgReg;                        /**< access flags */
} GOAL_DRV_MBOX_PL320_REG_T;


#endif /* MBOX_PL320_INT_H */
