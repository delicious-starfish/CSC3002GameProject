#include "gameCollection.h"
#include "gameRender.h"
#include <graphics.h>
#include <conio.h>

IMAGE grnd;
IMAGE belt;
IMAGE belC;
IMAGE rota;

void loadImgRes() {
	loadimage(&grnd, _T("tex\\grd1.png"));
	loadimage(&belt, _T("tex\\belt.png"));
	loadimage(&belC, _T("tex\\belC.png"));
	loadimage(&rota, _T("tex\\rota.png"));
}

void putAlphaImage(int x, int y, IMAGE* srcimg)
{
    DWORD* dst = GetImageBuffer(NULL);
    DWORD* src = GetImageBuffer(srcimg);
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int dst_width = getwidth();
    int dst_height = getheight();
    int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
    int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;
    if (x < 0) { src += -x;	iwidth -= -x;	x = 0; }
    if (y < 0) { src += src_width * -y;	iheight -= -y;	y = 0; }
    dst += dst_width * y + x;
    for (int iy = 0; iy < iheight; ++iy)
    {
        for (int i = 0; i < iwidth; ++i)
        {
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0)
                if (sa == 255)
                    dst[i] = src[i];
                else
                    dst[i] = ((((src[i] & 0xff0000) >> 16) + ((dst[i] & 0xff0000) >> 16) * (255 - sa) / 256) << 16) | ((((src[i] & 0xff00) >> 8) + ((dst[i] & 0xff00) >> 8) * (255 - sa) / 256) << 8) | ((src[i] & 0xff) + (dst[i] & 0xff) * (255 - sa) / 256);
        }
        dst += dst_width; src += src_width;
    }
}

void renderTick(World& world) {
	cleardevice();
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			switch (world.mapp[i][j].type)
			{
			case(GROUNDID):
				putAlphaImage(j* 32, i* 32, &grnd); break;
			case(BELTID):
				putAlphaImage(j * 32, i * 32, &belt); break;
			case(ROTATORID):
				putAlphaImage(j * 32, i * 32, &rota); break;

			}
		}
	}
}
