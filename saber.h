#ifndef	__SABER_H
#define	__SABER_H

enum	SaberEnable_e {
	SABER_GLOBAL_ENABLE	= 1,
	SABER_MIDBTN_ZOOM	= 1 << 1,
	SABER_RIGBTN_DRAG	= 1 << 2
};

UINT	SaberGetConf(void);
void	SaberSetConf(UINT value);
BOOL	SaberInit(void);

#endif


