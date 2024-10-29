#include "gameCollection.h"
#include "gameRender.h"
#include "gameBuildings.h"
#include <graphics.h>
#include <conio.h>

IMAGE mouse;
IMAGE grnd;
IMAGE beltup;
IMAGE beltdn;
IMAGE beltlf;
IMAGE beltrt;
IMAGE belC;
IMAGE cutt;
IMAGE rota;

void loadImgRes() {
    loadimage(&mouse, _T("tex\\click.png"));
	loadimage(&grnd, _T("tex\\grd1.png"));
	loadimage(&beltup, _T("tex\\belt-up.png"));
    loadimage(&beltdn, _T("tex\\belt-dn.png"));
    loadimage(&beltlf, _T("tex\\belt-lf.png"));
    loadimage(&beltrt, _T("tex\\belt-rt.png"));
	loadimage(&belC, _T("tex\\belC.png"));
    loadimage(&cutt, _T("tex\\cutt.png"));
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
    renderBuildings(world);
    renderMouse();
    
}

void renderBuildings(World& world) {
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &grnd);
        }
    }
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            switch (world.mapp[i][j].type)
            {
            case(BELTID):
                switch (world.belt[world.mapp[i][j].id].dir) {
                case UP:
                    putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &beltup);
                    break;
                case DOWN:
                    putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &beltdn);
                    break;
                case LEFT:
                    putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &beltlf);
                    break;
                case RIGHT:
                    putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &beltrt);
                    break;
                }
                break;
            case(ROTATORID):
                putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &rota); break;
            case(CUTTERID):
                if (world.mapp[i][j].isMain == true)
                    putAlphaImage(j * 32 + cameraPositionX, i * 32 + cameraPositionY, &cutt); break;

            }
        }
    }
}

void renderMouse() {
    putAlphaImage(mousePositionX - 16, mousePositionY - 16, &mouse);
}