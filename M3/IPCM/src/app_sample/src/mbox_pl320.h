/** @file
 *
 * @brief GOAL ARM PL320 Mailbox Driver
 *
 * @copyright
 * Copyright 2010-2017.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef MBOX_PL320_H
#define MBOX_PL320_H

//#include <goal_media/goal_ma_mbox.h>


/****************************************************************************/
/* Typedefs */
/****************************************************************************/
typedef enum {
    GOALDRV_MBOX_PL320_CFG_UNKNOWN = 0,         /**< invalid configuration */
    GOALDRV_MBOX_PL320_CFG_TX,                  /**< transmission only */
    GOALDRV_MBOX_PL320_CFG_RX,                  /**< receive only */
    GOALDRV_MBOX_PL320_CFG_TX_RX,               /**< transmission and receive allowed */
} GOALDRV_MBOX_PL320_CFG_T;


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
int goal_drvMboxPl320Reg(
    uint8_t *pAddrBase,                         /**< register address base */
    unsigned int idMbox,                        /**< own mailbox ID */
    unsigned int idMboxForeign,                 /**< foreign mailbox ID (used for TX) */
    uint32_t idEvent,                           /**< event ID */
    unsigned int cntDataReg,                    /**< count of data registers */
    GOALDRV_MBOX_PL320_CFG_T cfg                /**< configuration */
);

#endif /* MBOX_PL320_H */
