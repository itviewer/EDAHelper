#ifndef	__PADS_H
#define	__PADS_H

enum	PadsEnable_e {
	PADS_GLOBAL_ENABLE	= 1,
	PADS_MIDBTN_ZOOM	= 1 << 1,
	PADS_RIGBTN_DRAG	= 1 << 2,
	PADS_MIDBTN_SWITCH	= 1 << 3,
	PADS_RIGBTN_ROTATE	= 1 << 4,
	PADS_RIGBTN_DRAG_SMOOTH= 1 << 5
};

UINT	PadsGetConf(void);
void	PadsSetConf(UINT value);
BOOL PadsInit(void);

#endif


