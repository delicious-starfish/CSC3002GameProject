#include "gameCollection.h"
#include "gameRender.h"
#include "gameBuildings.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>

//UI
IMAGE UIframe1;
IMAGE UIframe2;
//Mouse
IMAGE mouse1;
IMAGE mouse2;
//Buildings
IMAGE grnd;
IMAGE belt;
IMAGE belC;
IMAGE cutt;
IMAGE rota;
//Items
IMAGE SqR;
IMAGE SqY;
IMAGE SqB;
IMAGE SqW;
IMAGE CcR;
IMAGE CcY;
IMAGE CcB;
IMAGE CcW;
IMAGE MlR;
IMAGE MlY;
IMAGE MlB;
IMAGE MlW;

void loadImgRes() {
    loadimage(&UIframe1, _T("tex\\UI-02-up.png"));
    loadimage(&UIframe2, _T("tex\\UI-02-dn.png"));
    loadimage(&mouse1, _T("tex\\clickout.png"));
    loadimage(&mouse2, _T("tex\\clickin.png"));
    loadimage(&grnd, _T("tex\\grnd.png"));
    loadimage(&belt, _T("tex\\belt.png"));
    loadimage(&belC, _T("tex\\belC.png"));
    loadimage(&cutt, _T("tex\\cutt.png"));
    loadimage(&rota, _T("tex\\rota.png"));
    loadimage(&SqR, _T("tex\\squr-R.png"));
    loadimage(&SqY, _T("tex\\squr-Y.png"));
    loadimage(&SqB, _T("tex\\squr-B.png"));
    loadimage(&SqW, _T("tex\\squr-W.png"));
    loadimage(&CcR, _T("tex\\ccle-R.png"));
    loadimage(&CcY, _T("tex\\ccle-Y.png"));
    loadimage(&CcB, _T("tex\\ccle-B.png"));
    loadimage(&CcW, _T("tex\\ccle-W.png"));
    loadimage(&MlR, _T("tex\\mill-R.png"));
    loadimage(&MlY, _T("tex\\mill-Y.png"));
    loadimage(&MlB, _T("tex\\mill-B.png"));
    loadimage(&MlW, _T("tex\\mill-W.png"));
}

IntImg::IntImg() {
    for (int iy = 0; iy < screenSizeY; iy++) {
        for (int ix = 0; ix < screenSizeX; ix++) {
            pixel[ix][iy] = 0;
        }
    }
}

void IntImg::putImg(int x, int y, IMAGE* srcimg, int direction=1, double scale =1) {
    DWORD* src = GetImageBuffer(srcimg);
    double vScale = 1 / scale;
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int src_X = src_width * src_height;
    int lx = (x > 0) ? x : 0;
    int ly = (y > 0) ? y : 0; 
    int Mx = (x + src_width * scale > screenSizeX) ? screenSizeX : x + src_width * scale;
    int My = (y + src_height * scale > screenSizeY) ? screenSizeY : y + src_height * scale;
    int i = 0;
    for (int iy = ly; iy < My; iy++){
        for (int ix = lx; ix < Mx; ix++){
            switch (direction) {
                case 1:i = (int)((iy - y)*vScale) * src_width + (ix - x)*vScale; break;
                case 2:i = (src_height - (int)((iy - y + 1)*vScale)) * src_width + src_width-1-(int)((ix - x)*vScale); break;
                case 3:i = (int)((ix - x)*vScale) * src_width + src_width - 1 - (int)(iy - y)*vScale; break;
                case 4:i = (src_width - (int)((ix - x + 1)*vScale)) * src_width + (int)((iy - y)*vScale); break;
            }
            i = (i < src_X&&i>=0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0){
                if (sa == 255){
                    pixel[ix][iy] = src[i];
                }
                else{
                    int sr = ((src[i] & 0xff0000) >> 16);	
                    int sg = ((src[i] & 0xff00) >> 8);		
                    int sb = src[i] & 0xff;				
                    int dr = ((pixel[ix][iy] & 0xff0000) >> 16);
                    int dg = ((pixel[ix][iy] & 0xff00) >> 8);
                    int db = pixel[ix][iy] & 0xff;
                    pixel[ix][iy] = ((sr + dr * (255 - sa) / 256) << 16) | ((sg + dg * (255 - sa) / 256) << 8) | (sb + db * (255 - sa) / 256);
                }
            }
        }
    }
}

void IntImg::putImg(int x, int y, double r, IMAGE* srcimg, double scale=1)
{
    DWORD* src = GetImageBuffer(srcimg);
    double vScale = 1 / scale;
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    float cosr = cos(r);
    float sinr = sin(r);
    int center_width;
    int center_height;
    int lx = (x > 0) ? x : 0;
    int ly = (y > 0) ? y : 0;
    int Mx = (x + src_width * scale > screenSizeX) ? screenSizeX : x + src_width * scale;
    int My = (y + src_height * scale > screenSizeY) ? screenSizeY : y + src_height * scale;
    center_width = scale *src_width / 2;
    center_height = scale *src_height / 2;
    int i = 0; int irx = 0; int iry = 0;
    int src_X = src_width * src_height;
    for (int iy = ly; iy < My; iy++) {
        for (int ix = lx; ix < Mx; ix++) {
            irx = (int)((ix - x - center_width) * cosr - (iy - y - center_height) * sinr + center_width);
            iry = (int)((iy - y - center_height) * cosr + (ix - x - center_width) * sinr + center_height);
            irx = (irx >= 0 && irx < src_width* scale) ? irx : 0;
            iry = (iry >= 0 && iry < src_height* scale) ? iry : 0;
            i = (int)(iry*vScale) *src_width  + irx*vScale;
            i = (i < src_X&&i>=0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0) {
                if (sa == 255) {
                    pixel[ix][iy] = src[i];
                }
                else {
                    int sr = ((src[i] & 0xff0000) >> 16);
                    int sg = ((src[i] & 0xff00) >> 8);
                    int sb = src[i] & 0xff;
                    int dr = ((pixel[ix][iy] & 0xff0000) >> 16);
                    int dg = ((pixel[ix][iy] & 0xff00) >> 8);
                    int db = pixel[ix][iy] & 0xff;
                    pixel[ix][iy] = ((sr + dr * (255 - sa) / 256) << 16) | ((sg + dg * (255 - sa) / 256) << 8) | (sb + db * (255 - sa) / 256);
                }
            }
        }
    }
}

void IntImg::RenderImg() {
    DWORD* dst = GetImageBuffer(NULL);
    for (int iy = 0; iy < screenSizeY; iy++){
        for (int ix = 0; ix < screenSizeX; ix++){
            dst[ix] = pixel[ix][iy];
        }
        dst += screenSizeX;
    }
}

void IntImg::ClearImg() {
    for (int iy = 0; iy < screenSizeY; iy++) {
        for (int ix = 0; ix < screenSizeX; ix++) {
            pixel[ix][iy] = 13594431;
        }
    }
}

void IntImg::putGrounds(){
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &grnd, 1, screenScale);
        }
    }
}

void IntImg::putBuildings(World& world){
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            switch (world.mapp[i][j].type)
            {
            case(BELTID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &belt, world.belt[world.mapp[i][j].id].dir, screenScale);
                break;
            case(ROTATORID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &rota, 1, screenScale); break;
            case(CUTTERID):
                if (world.mapp[i][j].isMain == true)
                    putImg((j * 64 - 32) * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &cutt, 2, screenScale); break;
            }
        }
    }
}

void IntImg::putItems(World& world){
    for (int i = 0; i < world.beltNum; i++) {
        if (!world.belt[i].isEmpty) {
            // The belt has item, start rendering
            Item itemRender = world.belt[i].itemNow;
            int YUp = world.belt[i].pos[0] * 64 * screenScale + cameraPositionY;
            int XLeft = world.belt[i].pos[1] * 64 * screenScale + cameraPositionX;
            int dir;
            int spANDcl;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; break;
                    case 1:dir = 4; break;
                    case 2:dir = 3; break;
                    case 3:dir = 2; break;
                    }
                    spANDcl = itemRender.shapeId[0][j][k]*8+itemRender.colorId[0][j][k];
                    //Determine which image to show
                    switch (spANDcl) {
                    case 9:
                        putImg(XLeft, YUp, &CcR, dir, screenScale); break;
                    case 10:
                        putImg(XLeft, YUp, &CcY, dir, screenScale); break;
                    case 11:
                        putImg(XLeft, YUp, &CcB, dir, screenScale); break;
                    case 12:
                        putImg(XLeft, YUp, &CcW, dir, screenScale); break;
                    case 17:
                        putImg(XLeft, YUp, &SqR, dir, screenScale); break;
                    case 18:
                        putImg(XLeft, YUp, &SqY, dir, screenScale); break;
                    case 19:
                        putImg(XLeft, YUp, &SqB, dir, screenScale); break;
                    case 20:
                        putImg(XLeft, YUp, &SqW, dir, screenScale); break;
                    case 25:
                        putImg(XLeft, YUp, &MlR, dir, screenScale); break;
                    case 26:
                        putImg(XLeft, YUp, &MlY, dir, screenScale); break;
                    case 27:
                        putImg(XLeft, YUp, &MlB, dir, screenScale); break;
                    case 28:
                        putImg(XLeft, YUp, &MlW, dir, screenScale); break;
                    }
                }
            }
            
        }
    }
}

void IntImg::putUI(){
    putImg(mousePositionX - 32 * screenScale, mousePositionY - 32 * screenScale, -mousePositionX / 12.57, &mouse1, screenScale);
    putImg(mousePositionX - 32, mousePositionY - 32, mousePositionY / 25.13, &mouse2);
    putImg(0, 0, &UIframe1);
    putImg(0, 396, &UIframe2);
}

void IntImg::renderTick(World& world) {
	ClearImg();
    putGrounds();
    putBuildings(world);
    putItems(world);
    putUI();
    RenderImg();
}
