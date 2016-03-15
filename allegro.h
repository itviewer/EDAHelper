#ifndef	__ALLEGRO_H
#define	__ALLEGRO_H

enum	AllegroEnable_e {
	ALLEGRO_GLOBAL_ENABLE	= 1,
	ALLEGRO_MIDBTN_ZOOM	= 1 << 1,
	ALLEGRO_MIDBTN_DRAG	= 1 << 2
};

UINT	AllegroGetConf(void);
void	AllegroSetConf(UINT value);
BOOL AllegroInit(void);

#endif



