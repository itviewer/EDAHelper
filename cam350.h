#ifndef	__CAM350_H
#define	__CAM350_H

enum	Cam350Enable_e {
	CAM350_GLOBAL_ENABLE	= 1,
	CAM350_MIDBTN_ZOOM		= 1 << 1,
	CAM350_MIDBTN_FITALL	= 1 << 2,
	CAM350_MIDBTN_MOVE		= 1 << 3,
	CAM350_RIGBTN_DRAG		= 1 << 4
};

UINT	Cam350GetConf(void);
void	Cam350SetConf(UINT value);
BOOL	Cam350Init(void);

#endif



