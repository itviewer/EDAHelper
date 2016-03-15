#ifndef	__ORCAD_H
#define	__ORCAD_H

enum	OrcadEnable_e {
	ORCAD_GLOBAL_ENABLE	= 1,
	ORCAD_MIDBTN_ZOOM	= 1 << 1,
	ORCAD_MIDBTN_PLACE	= 1 << 2,
	ORCAD_MIDBTN_MOVE	= 1 << 3,
	ORCAD_RIGBTN_DRAG	= 1 << 4,
	ORCAD_RIGBTN_DRAG_SCROLL	= 1 << 5,	// 模拟滚动
	ORCAD_RIGBTN_DRAG_C	= 1 << 6		// 模拟按键"C"
};

UINT	OrcadGetConf(void);
void	OrcadSetConf(UINT value);
BOOL	OrcadInit(void);

#endif



