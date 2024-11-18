#include "gameCollection.h"
#include "gameRender.h"
#include "gameBuildings.h"
#include "constants.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include "gameControl.h"

//UI
IMAGE UIframe1;
IMAGE UIframe2;
IMAGE UIbelt;
IMAGE UIdivi;
IMAGE UIcomp;
IMAGE UIrota;
IMAGE UIcolr;
IMAGE UIBlight;
IMAGE UIbdscr0;
IMAGE UIbdscr1;
IMAGE UIbdscr2;
IMAGE UIbdscr3;
IMAGE UIbdscr4;
IMAGE UIbdscr5;
IMAGE beltOO;
IMAGE cuttOO;
//Mouse
IMAGE mouse1;
IMAGE mouse2;
//Buildings
IMAGE grnd;
IMAGE belt;
IMAGE belC;
IMAGE cutt;
IMAGE rota;
IMAGE miner;
IMAGE bin;
//Items
IMAGE SqR;
IMAGE SqY;
IMAGE SqB;
IMAGE SqW;
IMAGE SquI;
IMAGE SqnI;
IMAGE CcR;
IMAGE CcY;
IMAGE CcB;
IMAGE CcW;
IMAGE CcuI;
IMAGE CcnI;
IMAGE MlR;
IMAGE MlY;
IMAGE MlB;
IMAGE MlW;
IMAGE MluI;
IMAGE MlnI;
//Illum
IMAGE shadow;

//温馨提示：这里一大堆资源，没事别动这个函数，不然IDE可能会变得有点卡
void loadImgRes() {
    loadimage(&UIframe1, _T("tex\\UI-02-up.png"));
    loadimage(&UIframe2, _T("tex\\UI-02-dn.png"));
    loadimage(&UIbelt, _T("tex\\UI-Belt.png"));
    loadimage(&UIdivi, _T("tex\\UI-Divi.png"));
    loadimage(&UIcomp, _T("tex\\UI-Comp.png"));
    loadimage(&UIrota, _T("tex\\UI-Roto.png"));
    loadimage(&UIcolr, _T("tex\\UI-Colr.png"));
    loadimage(&UIBlight, _T("tex\\UI-Blight.png"));
    loadimage(&UIbdscr0, _T("tex\\UI-description0.png"));
    loadimage(&UIbdscr1, _T("tex\\UI-description1.png"));
    loadimage(&UIbdscr2, _T("tex\\UI-description2.png"));
    loadimage(&UIbdscr3, _T("tex\\UI-description3.png"));
    loadimage(&UIbdscr4, _T("tex\\UI-description4.png"));
    loadimage(&UIbdscr5, _T("tex\\UI-description5.png"));
    loadimage(&beltOO, _T("tex\\beltOO.png"));
    loadimage(&cuttOO, _T("tex\\cuttOO.png"));
    loadimage(&mouse1, _T("tex\\clickout.png"));
    loadimage(&mouse2, _T("tex\\clickin.png"));
    loadimage(&grnd, _T("tex\\grnd.png"));
    loadimage(&belt, _T("tex\\belt.png"));
    loadimage(&belC, _T("tex\\belC.png"));
    loadimage(&cutt, _T("tex\\cutt.png"));
    loadimage(&rota, _T("tex\\rota.png"));
    loadimage(&miner, _T("tex\\miner.png"));
    loadimage(&bin, _T("tex\\rubbishBin.png"));
    loadimage(&SqR, _T("tex\\squr-R.png"));
    loadimage(&SqY, _T("tex\\squr-Y.png"));
    loadimage(&SqB, _T("tex\\squr-B.png"));
    loadimage(&SqW, _T("tex\\squr-W.png"));
    loadimage(&SquI, _T("tex\\squr-uI.png"));
    loadimage(&SqnI, _T("tex\\squr-nI.png"));
    loadimage(&CcR, _T("tex\\ccle-R.png"));
    loadimage(&CcY, _T("tex\\ccle-Y.png"));
    loadimage(&CcB, _T("tex\\ccle-B.png"));
    loadimage(&CcW, _T("tex\\ccle-W.png"));
    loadimage(&CcuI, _T("tex\\ccle-uI.png"));
    loadimage(&CcnI, _T("tex\\ccle-nI.png"));
    loadimage(&MlR, _T("tex\\mill-R.png"));
    loadimage(&MlY, _T("tex\\mill-Y.png"));
    loadimage(&MlB, _T("tex\\mill-B.png"));
    loadimage(&MlW, _T("tex\\mill-W.png"));
    loadimage(&MluI, _T("tex\\mill-uI.png"));
    loadimage(&MlnI, _T("tex\\mill-nI.png"));
    loadimage(&shadow, _T("tex\\shadow.png"));
}    

IntImg::IntImg() {
    leftBound = cameraPositionX / 64 - 32 * screenScale;
    rightBound = cameraPositionX / 64 + 32 * screenScale;
    upBound = cameraPositionY / 64 - 32 * screenScale;
    dnBound = cameraPositionY / 64 + 32 * screenScale;
    for (int iy = 0; iy < screenSizeY; iy++) {
        for (int ix = 0; ix < screenSizeX; ix++) {
            pixel[ix][iy] = 0;
            shade[ix][iy] = 0;
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

void IntImg::putShadow(int x, int y, IMAGE* srcimg, double scale) {
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
    for (int iy = ly; iy < My; iy++) {
        for (int ix = lx; ix < Mx; ix++) {
            i = (int)((iy - y) * vScale) * src_width + (ix - x) * vScale;
            i = (i < src_X && i >= 0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0 && sa > shade[ix][iy]) {
                int psa = shade[ix][iy];
                shade[ix][iy] = sa;
                int dr = ((pixel[ix][iy] & 0xff0000) >> 16);
                int dg = ((pixel[ix][iy] & 0xff00) >> 8);
                int db = pixel[ix][iy] & 0xff;
                pixel[ix][iy] = ((dr * (255 - sa) / (255 - psa)) << 16) | ((dg * (255 - sa) / (255 - psa)) << 8) | (db * (255 - sa) / (255 - psa));

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
            shade[ix][iy] = 0;
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
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            switch (world.mapp[i][j].type)
            {
            case(RUBBISHBINID)://No need to write anything here, it works
            case(ROTATORID):   //
            case(CUTTERID):    //
            case(MINERID):     //
            case(BELTID):
                putShadow((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &shadow, screenScale); break;
            }
        }
    }
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            switch (world.mapp[i][j].type)
            {
            case(BELTID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &belt, world.belt[world.mapp[i][j].id].dir, screenScale);
                break;
            case(ROTATORID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &rota, 1, screenScale); break;
            case(CUTTERID):
                if (world.mapp[i][j].isMain == true)
                    switch (world.cutter[world.mapp[i][j].id].dir) {
                    case 1:putImg((j * 64) * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &cutt, 1, screenScale); break;
                    case 2:putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cutt, 2, screenScale); break;
                    case 3:putImg((j * 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cutt, 3, screenScale); break;
                    case 4:putImg((j * 64 - 64) * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &cutt, 4, screenScale); break;
                    }
                break;
            case(MINERID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &miner, world.miner[world.mapp[i][j].id].dir, screenScale); break;
            case(RUBBISHBINID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &bin, UP, screenScale); break;
            }
            
        }
    }
}

void IntImg::putItems(World& world){
    for (int i = 0; i < world.maxBeltId; i++) {
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

void IntImg::putUI() {
    int scrscl64 = screenScale * 64;
    int UIbX = ((mousePositionX - cameraPositionX) / scrscl64) * scrscl64 + cameraPositionX;
    int UIbY = ((mousePositionY - cameraPositionY) / scrscl64) * scrscl64 + cameraPositionY;
    switch (mouseCase) {
    case NORMALCASE: {
        putImg(mousePositionX - 32 * screenScale, mousePositionY - 32 * screenScale, mousePositionY / 14.5 / screenScale, &mouse1, screenScale);
        putImg(mousePositionX - 32 * (screenScale / 2 + 0.5), mousePositionY - 32 * (screenScale / 2 + 0.5), -mousePositionX / 28.5 / screenScale, &mouse2, screenScale / 2 + 0.5); break;
    }
    case UIBELT: putImg(UIbX - 32 * screenScale, UIbY - 32 * screenScale, &beltOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr1); putImg(43, 440, &UIBlight); break;
    case UICUTTER: putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &cuttOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr3); putImg(237, 440, &UIBlight); break;
    }
    putImg(0, 0, &UIframe1);
    putImg(0, 396, &UIframe2);
    putImg(43, 443, &UIbelt);
    putImg(140, 443, &UIrota);
    putImg(237, 443, &UIdivi);
    putImg(334, 443, &UIcomp);
    putImg(431, 443, &UIcolr);
    switch (hoverCase) {
    case UIBELT:putImg(740, 435, &UIbdscr1); putImg(43, 440, &UIBlight); break;
    case UIROTATOR:putImg(740, 435, &UIbdscr2); putImg(140, 440, &UIBlight); break;
    case UICUTTER: putImg(740, 435, &UIbdscr3); putImg(237, 440, &UIBlight); break;
    case UICOMPOSER: putImg(740, 435, &UIbdscr4); putImg(334, 440, &UIBlight); break;
    case UICOLORER: putImg(740, 435, &UIbdscr5); putImg(431, 440, &UIBlight); break;
    }
    if (mouseCase == NORMALCASE && hoverCase == NORMALCASE) { putImg(740, 435, &UIbdscr0); }
}

void IntImg::blur() {
    int sum;
    int sr, sg, sb;
    int tr, tg, tb;
    int r = 8;
    for (int i = 45; i < screenSizeX - 235; i += 2) {
        for (int j = 442; j < screenSizeY - 4; j += 2) {
            tr = 0; tg = 0; tb = 0;
            for (int ir = -4; ir < 4; ir++) {
                for (int jr = -4; jr < 4; jr++) {
                    tr += ((pixel[i + ir][j + jr] & 0xff0000) >> 16);
                    tg += ((pixel[i + ir][j + jr] & 0xff00) >> 8);
                    tb += (pixel[i + ir][j + jr] & 0xff);
                }
            }
            sr = tr / r / r;
            sg = tg / r / r;
            sb = tb / r / r;
            sum = (sr << 16) | (sg << 8) | (sb);
            pixel[i][j] = sum; pixel[i + 1][j] = sum;
            pixel[i][j + 1] = sum; pixel[i + 1][j + 1] = sum;
        }
    }
}

void IntImg::renderTick(World& world) {
    ClearImg();
    leftBound = -cameraPositionX / 64 / screenScale;
    rightBound = (-cameraPositionX + screenSizeX + 64) / screenScale / 64;
    upBound = -cameraPositionY / 64 / screenScale;
    dnBound = (-cameraPositionY + screenSizeY + 64) / screenScale / 64;
    leftBound = (leftBound < 0) ? 0 : leftBound;
    rightBound = (rightBound > MAPLENGTH) ? MAPLENGTH : rightBound;
    upBound = (upBound < 0) ? 0 : upBound;
    dnBound = (dnBound > MAPLENGTH) ? MAPLENGTH : dnBound;
    putGrounds();
    putBuildings(world);
    putItems(world);
    blur();
    putUI();
    RenderImg();
}
