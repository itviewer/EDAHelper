#ifndef	__CCAM_H
#define	__CCAM_H

enum	CcamEnable_e {
	CCAM_GLOBAL_ENABLE	= 1,
	CCAM_MIDBTN_ZOOM	= 1 << 1,
	CCAM_RIGBTN_DRAG	= 1 << 2
};

UINT	CcamGetConf(void);
void			CcamSetConf(UINT value);
BOOL			CcamInit(void);

#endif


