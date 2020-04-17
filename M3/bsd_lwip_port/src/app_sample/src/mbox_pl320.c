/** @file
 *
 * @brief GOAL ARM PL320 Mailbox Driver
 *
 * @copyright
 * Copyright 2010-2017.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#define GOAL_ID GOAL_ID_TGT
//#include <goal_includes.h>
#include <C:\projects\HWI\bsd_lwip_port\src\app_sample\src\mbox_pl320.h>
#include <C:\projects\HWI\bsd_lwip_port\src\app_sample\src\mbox_pl320_int.h>


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_DRV_MBOX_PL320_MBOX_DEFAULT 0      /**< default mailbox for reading registers */


/****************************************************************************/
/* Private variables */
/****************************************************************************/
static GOAL_LOCK_T *pMboxPl320LockTx = NULL;    /**< MBOX Pl320 transmission lock */
static struct GOAL_DRV_MBOX_PL320_T *pListHdl = NULL;  /**< list of driver handles for polling */


/****************************************************************************/
/* Register table */
/****************************************************************************/
/* register enums */
#undef GOAL_DRV_MBOX_PL320_RV
#define GOAL_DRV_MBOX_PL320_RV(addrReg, nameReg, shfVal, mskVal, ofsSub, ofsNext, flgReg) nameReg
typedef enum {
    GOAL_DRV_MBOX_PL320_RV_LIST,
    GOAL_DRV_MBOX_PL320_VAL_END
} GOAL_DRV_MBOX_PL320_REG_ID_T;


/* register entries */
#undef GOAL_DRV_MBOX_PL320_RV
#define GOAL_DRV_MBOX_PL320_RV(addrReg, nameReg, shfVal, mskVal, ofsSub, ofsNext, flgReg) { addrReg, shfVal, mskVal, ofsSub, ofsNext, flgReg }
static GOAL_DRV_MBOX_PL320_REG_T tblReg[] = {
    GOAL_DRV_MBOX_PL320_RV_LIST,
};


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
static GOAL_STATUS_T goal_drvMboxPl320Alloc(
    GOAL_MA_MBOX_T *pMbox,                      /**< mailbox handle */
    GOAL_MA_MBOX_RECV_T funcRecv                /**< receive callback function */
);

static GOAL_STATUS_T goal_drvMboxPl320Free(
    GOAL_MA_MBOX_T *pMbox                       /**< mailbox handle */
);

static GOAL_STATUS_T goal_drvMboxPl320Poll(
    GOAL_MA_MBOX_T *pMbox                       /**< mailbox handle */
);

static GOAL_STATUS_T goal_drvMboxPl320Get(
    uint32_t *pMskMboxNew                       /**< mask of mailboxes with new data */
);

static GOAL_STATUS_T goal_drvMboxPl320DataRead(
    GOAL_DRV_MBOX_PL320_T *pHdl                 /**< PL320 handle */
);

static GOAL_STATUS_T goal_drvMboxPl320DataWrite(
    GOAL_MA_MBOX_T *pMbox,                      /**< mailbox handle */
    uint8_t *pData,                             /**< data ptr */
    unsigned int len                            /**< data length */
);

static GOAL_STATUS_T goal_drvMboxPl320RegRead(
    GOAL_DRV_MBOX_PL320_T *pHdl,                /**< PL320 handle */
    unsigned int addrReg,                       /**< register address */
    unsigned int entryIdx,                      /**< index of the register entry */
    unsigned int idxSub,                        /**< sub-address index */
    uint32_t *pVal                              /**< ref to store value */
);

static GOAL_STATUS_T goal_drvMboxPl320RegWrite(
    GOAL_DRV_MBOX_PL320_T *pHdl,                /**< PL320 handle */
    unsigned int addrReg,                       /**< register address */
    unsigned int idxSub,                        /**< sub-address index */
    uint32_t val                                /**< value */
);

static GOAL_STATUS_T goal_drvMboxPl320IdSrcSet(
    GOAL_MA_MBOX_T *pMbox,                      /**< PL320 handle */
    uint32_t idSource                           /**< Source ID */
);

static GOAL_STATUS_T goal_drvMboxPl320IdDstSet(
    GOAL_MA_MBOX_T *pMbox,                      /**< mailbox handle */
    uint32_t idDestination                      /**< Destiantion ID */
);

static GOAL_STATUS_T goal_drvMboxPl320IdDstPurge(
    GOAL_MA_MBOX_T *pMbox                       /**< mailbox handle */
);

static GOAL_STATUS_T goal_drvMboxPl320IsrMskPurge(
    GOAL_MA_MBOX_T *pMbox                       /**< mailbox handle */
);

static GOAL_STATUS_T goal_drvMboxPl320IsrMskSet(
    GOAL_MA_MBOX_T *pMbox,                      /**< mailbox handle */
    uint32_t idChannel                          /**< Source ID */
);


/****************************************************************************/
/* Makros */
/****************************************************************************/
/* get the byte length of the usable mailbox data (message) */
#define GOAL_DRV_MBOX_PL320_MSG_LEN_GET(pHdl) \
    (((pHdl)->cntDataReg - 1) * sizeof((pHdl)->valTmp[0]))


/****************************************************************************/
/** Initialize PL320 Mailbox Driver
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_drvMboxPl320Reg(
    uint8_t *pAddrBase,                         /**< register address base */
    unsigned int idMbox,                        /**< own mailbox ID */
    unsigned int idMboxForeign,                 /**< foreign mailbox ID (used for TX) */
    uint32_t idEvent,                           /**< event ID */
    unsigned int cntDataReg,                    /**< count of data registers */
    GOALDRV_MBOX_PL320_CFG_T cfg                /**< configuration */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_DRV_MBOX_PL320_T *pHdl = NULL;         /* PL320 handle */
    GOAL_DRV_MBOX_PL320_T *pHdlIdx = NULL;      /* PL320 index handle */
    GOAL_MA_MBOX_T *pMbox = NULL;               /* mailbox MA handle */

    /* check if the configure is already used */
    GOAL_LL_FOREACH(pListHdl, pHdlIdx) {
        if ((idMbox == pHdlIdx->idMbox) && (idEvent == pHdlIdx->idEvent)) {
            goal_logErr("mailbox ID %u and event ID %"FMT_u32" is already used", idMbox, idEvent);
            return GOAL_ERR_PARAM;
        }
    }

    /* allocate PL320 handle */
    res = goal_memCalloc(&pHdl, sizeof(GOAL_DRV_MBOX_PL320_T));
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to allocate memory for PL320 mailbox");
        return res;
    }
    /* initialize driver details */
    pHdl->pAddrBase = pAddrBase;
    pHdl->idMbox = idMbox;
    pHdl->idMboxForeign = idMboxForeign;
    pHdl->idEvent = idEvent;
    pHdl->cntDataReg = cntDataReg;
    pHdl->cfg = cfg;

    /* save the MA handle for polling */
    res = goal_maMboxReg(&pMbox, goal_drvMboxPl320Poll, goal_drvMboxPl320DataWrite, goal_drvMboxPl320Alloc, goal_drvMboxPl320Free, pHdl);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to register mailbox media adapter");
        return res;
    }

    /* assign the mailbox MA handle */
    pHdl->pMaMbox = pMbox;

    /* add the entry to the linked list of driver handles */
    GOAL_LL_APPEND(pListHdl, pHdl);

    /* create resource lock */
    if (NULL == pMboxPl320LockTx) {
        res = goal_lockCreate(GOAL_LOCK_BINARY, &pMboxPl320LockTx, 0, 1, GOAL_ID_DRV_MBOX_PL320);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to create resource lock");
            return res;
        }
    }

    return res;
}


/****************************************************************************/
/** Allocate a Mailbox handle
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320Alloc(
    GOAL_MA_MBOX_T *pMbox,                      /**< mailbox handle */
    GOAL_MA_MBOX_RECV_T funcRecv                /**< receive callback function */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    UNUSEDARG(funcRecv);

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    if ((GOALDRV_MBOX_PL320_CFG_TX == pHdl->cfg) || (GOALDRV_MBOX_PL320_CFG_TX_RX == pHdl->cfg)) {

        /* Purge destination ID of Tx mailbox which is used for data retrieve acknowledgement */
        /* the mailbox ID of the handle is equal to the bit number for the source ID reg value */
        res = goal_drvMboxPl320IdDstPurge(pMbox);
        if (GOAL_RES_ERR(res)) {
            goal_logInfo("Failed to clean destination ID(s) of ARM PL320 mailbox.");
            return res;
        }

        /* Set source ID of Tx mailbox */
        res = goal_drvMboxPl320IdSrcSet(pMbox, (1 << pHdl->idMbox));
        if (GOAL_RES_ERR(res)) {
            goal_logInfo("Failed to setup source ID of ARM PL320 mailbox.");
            return res;
        }

        /* Purge interrupt mask Tx mailbox */
        res = goal_drvMboxPl320IsrMskPurge(pMbox);
        if (GOAL_RES_ERR(res)) {
            goal_logInfo("Failed to clean interrupts mask register of ARM PL320 mailbox.");
            return res;
        }

        /* Set destination ID of Tx mailbox */
        /* the foreign mailbox ID of the handle is equal to the bit number for the destination ID reg value */
        res = goal_drvMboxPl320IsrMskSet(pMbox, (1 << pHdl->idMboxForeign));
        if (GOAL_RES_ERR(res)) {
            goal_logInfo("Failed to set interrupt mask register of ARM PL320 mailbox.");
            return res;
        }
    }

    return res;
}


/****************************************************************************/
/** Free a Mailbox handle
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320Free(
    GOAL_MA_MBOX_T *pMbox                       /**< mailbox handle */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* prohibit sending */
    pHdl->cfg = GOALDRV_MBOX_PL320_CFG_UNKNOWN;

    /* Purge destination ID of Tx mailbox which is used for data retrieve acknowledgement */
    res = goal_drvMboxPl320IdDstPurge(pMbox);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("Failed to clean destination ID(s) of ARM PL320 mailbox.");
        return res;
    }

    /* Purge interrupt mask Tx mailbox */
    res = goal_drvMboxPl320IsrMskPurge(pMbox);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("Failed to clean interrupts mask register of ARM PL320 mailbox.");
        return res;
    }

    return res;
}


/****************************************************************************/
/** Polling the Mailbox
 *
 * This function reads all mailboxes with new data.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320Poll(
    GOAL_MA_MBOX_T *pMbox                       /**< mailbox handle */
)
{
    GOAL_STATUS_T res;                          /* result */
    uint32_t mskMboxNew = 0;                    /* mask of mailboxes with new data */
    GOAL_DRV_MBOX_PL320_T *pHdlIdx = NULL;      /* PL320 index handle */

    UNUSEDARG(pMbox);

    /* get a bit mask of mailboxes with new data */
    res = goal_drvMboxPl320Get(&mskMboxNew);
    /* Evaluation of res is not necessary, because the mask of mailboxes is zero in
     * case of an error. The following iteration will not find any match. */

    GOAL_LL_FOREACH(pListHdl, pHdlIdx) {
        if (GOAL_BIT_IS_SET(mskMboxNew, pHdlIdx->idMbox)) {
            res = goal_drvMboxPl320DataRead(pHdlIdx);
            if (GOAL_RES_OK(res)) {
                /* clear the bitmask bit, thus not all mailboxes has to be checked */
                GOAL_BIT_CLR(mskMboxNew, pHdlIdx->idMbox);
                return res;
            }
        }
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("Receiving a mailbox message causes an error");
    }

    return res;
}


/****************************************************************************/
/** Get a Mailbox with new data
 *
 * This function detects mailboxes with new data by evaluating the IPCM
 * status register and returns them as a bit mask.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320Get(
    uint32_t *pMskMboxNew                       /**< [out] mask of mailboxes with new data */
)
{
    /* check mailbox handle */
    if (NULL == pListHdl) {
        return GOAL_ERR_NULL_POINTER;
    }

    return goal_drvMboxPl320RegRead(pListHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_INT_MSK_STATUS, GOAL_TGT_MBOX_PL320_SRC_ID, 0, pMskMboxNew);
}


/****************************************************************************/
/** Read Mailbox Data Registers
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320DataRead(
    GOAL_DRV_MBOX_PL320_T *pHdl                 /**< PL320 handle */
)
{
    GOAL_STATUS_T res;                          /* result */
    unsigned int cnt;                           /* counter */

    /* read the data registers */
    for (cnt = 0; cnt < pHdl->cntDataReg; cnt++) {
        res = goal_drvMboxPl320RegRead(pHdl, GOAL_DRV_MBOX_PL320_REG_DATA, pHdl->idMbox, cnt, &pHdl->valTmp[cnt]);
        if (GOAL_RES_ERR(res)) {
            return res;
        }
    }

    /* set mailbox to idle */
    res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSEND, 0, GOAL_DRV_MBOX_PL320_IPCMXSEND_SEND_INACTIVE);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    /* skip if reading is not allowed */
    if ((GOALDRV_MBOX_PL320_CFG_RX != pHdl->cfg) && (GOALDRV_MBOX_PL320_CFG_TX_RX != pHdl->cfg)) {
        return GOAL_ERR_UNSUPPORTED;
    }

    /* validate the event ID */
    if (pHdl->valTmp[0] != pHdl->idEvent) {
        return GOAL_ERR_MISMATCH;
    }

    /* call the receive callback - reduced by 4 byte event ID */
    return goal_maMboxRecv(pHdl->pMaMbox, (uint8_t *) &pHdl->valTmp[1], GOAL_DRV_MBOX_PL320_MSG_LEN_GET(pHdl));
}


/****************************************************************************/
/** Write Mailbox Data Registers
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320DataWrite(
    GOAL_MA_MBOX_T *pMbox,                      /**< mailbox handle */
    uint8_t *pData,                             /**< data ptr */
    unsigned int len                            /**< data length */
)
{
    GOAL_STATUS_T res;                          /* result */
    unsigned int cnt;                           /* counter */
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */
    uint32_t val = 0;                           /* register value */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* check if the handle is valid for transmission */
    if ((GOALDRV_MBOX_PL320_CFG_TX != pHdl->cfg) && (GOALDRV_MBOX_PL320_CFG_TX_RX != pHdl->cfg)) {
        return GOAL_ERR_UNSUPPORTED;
    }

    /* validate the availbale data length - consider 4 byte event ID */
    if ((GOAL_DRV_MBOX_PL320_MSG_LEN_GET(pHdl)) < len) {
        return GOAL_ERR_PARAM;
    }

    /* Acquire lock */
    res = goal_lockGet(pMboxPl320LockTx, GOAL_LOCK_INFINITE);
    if (GOAL_RES_ERR(res)) {
        goal_lockPut(pMboxPl320LockTx);
        return res;
    }

    /* check if mailbox source ID is set */
    res = goal_drvMboxPl320RegRead(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSOURCE, pHdl->idMbox, 0, &val);
    if (GOAL_RES_ERR(res)) {
        goal_lockPut(pMboxPl320LockTx);
        return res;
    }
    if (GOAL_DRV_MBOX_PL320_IPCMXSOURCE_NOT_SET == val) {
        goal_logErr("mailbox source ID is not initialized");
        goal_lockPut(pMboxPl320LockTx);
        return GOAL_ERR_INIT;
    }

    res = goal_drvMboxPl320RegRead(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSEND, pHdl->idMbox, 0, &val);
    /* error check */
    if (GOAL_RES_ERR(res)) {
        goal_lockPut(pMboxPl320LockTx);
        return res;
    }
    if (GOAL_DRV_MBOX_PL320_IPCMXSEND_SEND_INACTIVE != val) {
        goal_lockPut(pMboxPl320LockTx);
        return GOAL_ERR_BUSY;
    }

    /* copy the event ID into the first register space */
    pHdl->valTmp[0] = pHdl->idEvent;
    /* append data buffer into register space */
    GOAL_MEMCPY(&pHdl->valTmp[1], pData, len);

    /* write all available data registers */
    for (cnt = 0; cnt < pHdl->cntDataReg; cnt++) {
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_DATA, cnt, pHdl->valTmp[cnt]);
        if (GOAL_RES_ERR(res)) {
            goal_lockPut(pMboxPl320LockTx);
            return res;
        }
    }

    /* Set destination ID of transmision mailbox */
    res = goal_drvMboxPl320IdDstSet(pMbox, GOAL_TGT_MBOX_PL320_DST_ID_REGVAL);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("Failed to clean destination ID(s) ARM PL320 mailbox.");
    }

    /* start transfer to destination */
    res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSEND, 0, GOAL_DRV_MBOX_PL320_IPCMXSEND_SEND_DEST);
    if (GOAL_RES_ERR(res)) {
        goal_lockPut(pMboxPl320LockTx);
        return res;
    }

    /* free lock */
    goal_lockPut(pMboxPl320LockTx);

    return GOAL_OK;
}


/****************************************************************************/
/** Read PL320 Register
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320RegRead(
    GOAL_DRV_MBOX_PL320_T *pHdl,                /**< PL320 handle */
    unsigned int addrReg,                       /**< register address */
    unsigned int entryIdx,                      /**< index of the register entry */
    unsigned int idxSub,                        /**< sub-address index */
    uint32_t *pVal                              /**< ref to store value */
)
{
    uint32_t *pReg;                             /* register pointer */

    /* check access flags */
    if (GOAL_REG_FLG_WO & tblReg[addrReg].flgReg) {
        return GOAL_ERR_ACCESS;
    }

    /* calculate register absolute address */
    pReg = (uint32_t *) (((uint8_t *) pHdl->pAddrBase + tblReg[addrReg].addrReg + (tblReg[addrReg].ofsNext * entryIdx)) + (idxSub * tblReg[addrReg].ofsSub));

    /* read and convert register content */
    *pVal = (*pReg >> tblReg[addrReg].valShift) & tblReg[addrReg].valMask;

    return GOAL_OK;
}


/****************************************************************************/
/** Write PL320 Register
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320RegWrite(
    GOAL_DRV_MBOX_PL320_T *pHdl,                /**< PL320 handle */
    unsigned int addrReg,                       /**< register address */
    unsigned int idxSub,                        /**< sub-address index */
    uint32_t val                                /**< value */
)
{
    uint32_t *pReg;                             /* register pointer */
    uint32_t valTmp;                            /* temporary value */

    /* check access flags */
    if (GOAL_REG_FLG_RO & tblReg[addrReg].flgReg) {
        return GOAL_ERR_ACCESS;
    }

    /* calculate register absolute address */
    pReg = (uint32_t *) (((uint8_t *) pHdl->pAddrBase + tblReg[addrReg].addrReg + (tblReg[addrReg].ofsNext * pHdl->idMbox)) + (idxSub * tblReg[addrReg].ofsSub));

    /* convert and write register content */
    valTmp = *pReg;
    valTmp &= ~(tblReg[addrReg].valMask << tblReg[addrReg].valShift);
    *pReg = valTmp | ((val & tblReg[addrReg].valMask) << tblReg[addrReg].valShift);

    return GOAL_OK;
}


/****************************************************************************/
/** Setup PL320 Mailbox Source ID
 *
 * Set up source ID of the mailbox and verifies the value.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320IdSrcSet(
    GOAL_MA_MBOX_T *pMbox,                      /**< PL320 handle */
    uint32_t idSource                           /**< Source ID */
)
{
    uint32_t val;                               /* temporary register value */
    GOAL_STATUS_T res;                          /* GOAL function result */
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* check if requested source id is valid */
    if ((idSource) & ~(GOAL_DRV_MBOX_PL320_DFLT_MSK_3_BIT)) {
        goal_logErr("Requested ID is invalid.");
        return GOAL_ERR_PARAM;
    }

    /* check if requested source id is one-hot encoded */
    /* TODO */

    /* read source ID from mailbox */
    res = goal_drvMboxPl320RegRead(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSOURCE, pHdl->idMbox, 0, &val);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    /* set source id if not already set as requested */
    if (val != idSource) {

        /* clear mailbox source id register according to the manual */
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSOURCE, 0, GOAL_DRV_MBOX_PL320_IPCMXSOURCE_NOT_SET);
        if (GOAL_RES_ERR(res)) {
            return res;
        }

        /* set mailbox source id register */
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSOURCE, 0, idSource);
        if (GOAL_RES_ERR(res)) {
            return res;
        }

        /* verify source id register according to manual by reading the register value until set */
        do {
            /* read source ID from mailbox */
            res = goal_drvMboxPl320RegRead(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMXSOURCE, pHdl->idMbox, 0, &val);
            if (GOAL_RES_ERR(res)) {
                return res;
            }
        } while (val != idSource);
    }

    return res;
}


/****************************************************************************/
/** Setup PL320 Mailbox Destination ID
 *
 * Adds the given destination ID to the corresponding register.
 *
 * Warning:
 * This function does not set the destination as a one-hot encoded value
 * to the register.
 * Therefore already present destination ID bits will remain.
 *
 * To clean the destination register use the function
 *
 * @returns GOAL_STATUS_T result goal_drvMboxPl320PurgeDst().
 */
static GOAL_STATUS_T goal_drvMboxPl320IdDstSet(
    GOAL_MA_MBOX_T *pMbox,                      /**< PL320 handle */
    uint32_t idDestination                      /**< Source ID */
)
{
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* check if requested idDestination id is valid */
    if ((idDestination) & ~(GOAL_DRV_MBOX_PL320_DFLT_MSK_3_BIT)) {
        goal_logErr("Requested destination ID is invalid.");
        return GOAL_ERR_PARAM;
    }

    /* set mailbox idDestination id register */
    return goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_SET, 0, idDestination);
}


/****************************************************************************/
/** Purge interrupt mask register
 *
 * This function removes all target destinations from the message box.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320IsrMskPurge(
    GOAL_MA_MBOX_T *pMbox                       /**< PL320 handle */
)
{
    GOAL_STATUS_T res;                          /* GOAL function result */
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* clear mailbox destination bit 0 */
    res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_CLEAR, 0, GOAL_DRV_MBOX_PL320_SOURCE_0);

    if (GOAL_RES_OK(res)) {
        /* clear mailbox destination bit 1 */
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_CLEAR, 0, GOAL_DRV_MBOX_PL320_SOURCE_1);
    }

    if (GOAL_RES_OK(res)) {
        /* clear mailbox destination bit 2 */
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_CLEAR, 0, GOAL_DRV_MBOX_PL320_SOURCE_2);
    }

    return res;
}


/****************************************************************************/
/** Setup PL320 Mailbox Interrupt Mask
 *
 * This function sets the interrupt mask register for a set source ID.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320IsrMskSet(
    GOAL_MA_MBOX_T *pMbox,                      /**< PL320 handle */
    uint32_t idChannel                          /**< Source ID */
)
{
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* check if requested pIdDestination id is valid */
    if ((idChannel) & ~(GOAL_DRV_MBOX_PL320_DFLT_MSK_3_BIT)) {
        goal_logErr("Requested destination ID is invalid.");
        return GOAL_ERR_PARAM;
    }

    /* set mailbox pIdDestination id register */
    return goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_MSK_SET, 0, idChannel);
}


/****************************************************************************/
/** Purge destination register
 *
 * This function removes all target destinations from the message box.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_drvMboxPl320IdDstPurge(
    GOAL_MA_MBOX_T *pMbox                       /**< PL320 handle */
)
{
    GOAL_STATUS_T res;                          /* GOAL function result */
    GOAL_DRV_MBOX_PL320_T *pHdl;                /* PL320 handle */

    /* check mailbox handle */
    if ((NULL == pMbox) || (NULL == pMbox->pData)) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* assign private data */
    pHdl = (GOAL_DRV_MBOX_PL320_T *) pMbox->pData;

    /* clear mailbox destination bit 0 */
    res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_CLR, 0, GOAL_DRV_MBOX_PL320_SOURCE_0);

    if (GOAL_RES_OK(res)) {
        /* clear mailbox destination bit 1 */
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_CLR, 0, GOAL_DRV_MBOX_PL320_SOURCE_1);
    }

    if (GOAL_RES_OK(res)) {
        /* clear mailbox destination bit 2 */
        res = goal_drvMboxPl320RegWrite(pHdl, GOAL_DRV_MBOX_PL320_REG_IPCMX_DST_CLR, 0, GOAL_DRV_MBOX_PL320_SOURCE_2);
    }

    return res;
}
