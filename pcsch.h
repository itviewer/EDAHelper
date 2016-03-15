#ifndef	__PCSCH_H
#define	__PCSCH_H

enum	PcschEnable_e {
	PCSCH_GLOBAL_ENABLE	= 1,
	PCSCH_MIDBTN_ZOOM	= 1 << 1,
	PCSCH_RIGBTN_DRAG	= 1 << 2
};

UINT	PcschGetConf(void);
void			PcschSetConf(UINT value);
BOOL			PcschInit(void);

#endif


