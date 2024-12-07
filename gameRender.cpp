#include "gameCollection.h"
#include "gameRender.h"
#include "gameBuildings.h"
#include "constants.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include "gameControl.h"
#include "gameConfig.h"
#include "gameUtil.h"

//UI
IMAGE UIframe1;
IMAGE UIframe2;
IMAGE UIbelt;
IMAGE UIdivi;
IMAGE UIcomp;
IMAGE UIrota;
IMAGE UIcolr;
IMAGE UIdes;
IMAGE UIBlight;
IMAGE UIbdscr0;
IMAGE UIbdscr1;
IMAGE UIbdscr2;
IMAGE UIbdscr3;
IMAGE UIbdscr4;
IMAGE UIbdscr5;
IMAGE UIbdscr6;
IMAGE UIbdscrE;
IMAGE UIbdscrT;
IMAGE beltOO;
IMAGE cuttOO;
IMAGE compOO;
IMAGE rotaOO;
IMAGE dstrOO;
IMAGE pauseBT;
IMAGE speedBT;
IMAGE speedBT2x;
IMAGE speedBT2xR;
IMAGE pauseTX;
//Mouse
IMAGE mouse1;
IMAGE mouse2;
//Buildings
IMAGE grnd;
IMAGE belt;
IMAGE beltU;
IMAGE beltD;
IMAGE beltL;
IMAGE beltR;
IMAGE beltPU;
IMAGE beltPD;
IMAGE beltPL;
IMAGE beltPR;
IMAGE belti;
IMAGE belC;
IMAGE cutt;
IMAGE cuttU;
IMAGE cuttD;
IMAGE cuttL;
IMAGE cuttR;
IMAGE cutti;
IMAGE comp;
IMAGE compU;
IMAGE compD;
IMAGE compL;
IMAGE compR;
IMAGE compi;
IMAGE rota;
IMAGE rotaU;
IMAGE rotaD;
IMAGE rotaL;
IMAGE rotaR;
IMAGE rotai;
IMAGE miner;
IMAGE mineri;
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
IMAGE shadowM;
IMAGE shadowU;
IMAGE shadowL;
IMAGE shadowLU;
IMAGE shadowLD;
IMAGE shadowD;
IMAGE shadowRU;
IMAGE shadowRD;
IMAGE shadowR;


TCHAR* StrToTchar(const std::string& str)
{
    TCHAR result[BUFFERSIZE];
    char c[BUFFERSIZE];
    strcpy_s(c, str.c_str());
    MultiByteToWideChar(CP_ACP, 0, c, -1, result, BUFFERSIZE);
    return result;
}

bool fileExist(const std::string& filePath)
{
    DWORD fileAttr = GetFileAttributesA(filePath.c_str());
    return (fileAttr != INVALID_FILE_ATTRIBUTES && !(fileAttr & FILE_ATTRIBUTE_DIRECTORY));
}

//温馨提示：这里一大堆资源，没事别动这个函数，不然IDE可能会变得有点卡
void loadImgRes() {

    // solve the question of loading the image resources without the VS IDE
    // when the tex path been changed, adjust the path in ini file
    // By X

    std::string strDefaultPath = "tex\\";
    std::string StrTexPath =
        GameConfig::getInstance().get("Resource", "TexPath", strDefaultPath);
    Logger::getInstance().log(Logger::DEBUG, "StrTexPath=" + StrTexPath);
    //
    if (!fileExist(StrTexPath + "UI-02-up.png"))
    {
        Logger::getInstance().log(Logger::ERR,
            "Resource load failed=" + StrTexPath + "UI-02-up.png");
    }

    loadimage(&UIframe1, StrToTchar(StrTexPath + "UI-03-up.png"));
    loadimage(&UIframe2, StrToTchar(StrTexPath + "UI-02-dn.png"));
    loadimage(&UIbelt, StrToTchar(StrTexPath + "UI-Belt.png"));
    loadimage(&UIdivi, StrToTchar(StrTexPath + "UI-Divi.png"));
    loadimage(&UIcomp, StrToTchar(StrTexPath + "UI-Comp.png"));
    loadimage(&UIrota, StrToTchar(StrTexPath + "UI-Roto.png"));
    loadimage(&UIcolr, StrToTchar(StrTexPath + "UI-Colr.png"));
    loadimage(&UIdes, StrToTchar(StrTexPath + "UI-Dstr.png"));
    loadimage(&UIBlight, StrToTchar(StrTexPath + "UI-Blight.png"));
    loadimage(&UIbdscr0, StrToTchar(StrTexPath + "UI-description0.png"));
    loadimage(&UIbdscr1, StrToTchar(StrTexPath + "UI-description1.png"));
    loadimage(&UIbdscr2, StrToTchar(StrTexPath + "UI-description2.png"));
    loadimage(&UIbdscr3, StrToTchar(StrTexPath + "UI-description3.png"));
    loadimage(&UIbdscr4, StrToTchar(StrTexPath + "UI-description4.png"));
    loadimage(&UIbdscr5, StrToTchar(StrTexPath + "UI-description5.png"));
    loadimage(&UIbdscr6, StrToTchar(StrTexPath + "UI-description6.png"));
    loadimage(&UIbdscrE, StrToTchar(StrTexPath + "UI-descriptionE.png"));
    loadimage(&UIbdscrT, StrToTchar(StrTexPath + "UI-descriptionT.png"));
    loadimage(&beltOO, StrToTchar(StrTexPath + "beltOO.png"));
    loadimage(&cuttOO, StrToTchar(StrTexPath + "cuttOO.png"));
    loadimage(&compOO, StrToTchar(StrTexPath + "compOO.png"));
    loadimage(&rotaOO, StrToTchar(StrTexPath + "rotaOO.png"));
    loadimage(&dstrOO, StrToTchar(StrTexPath + "dstrOO.png"));
    loadimage(&pauseBT, StrToTchar(StrTexPath + "UI-pauseBT.png"));
    loadimage(&speedBT, StrToTchar(StrTexPath + "UI-speedBT.png"));
    loadimage(&speedBT2x, StrToTchar(StrTexPath + "UI-speedBT2x.png"));
    loadimage(&speedBT2xR, StrToTchar(StrTexPath + "UI-speedBT2x-R.png"));
    loadimage(&pauseTX, StrToTchar(StrTexPath + "UI-pause.png"));
    loadimage(&mouse1, StrToTchar(StrTexPath + "clickout.png"));
    loadimage(&mouse2, StrToTchar(StrTexPath + "clickin.png"));
    loadimage(&grnd, StrToTchar(StrTexPath + "grnd.png"));
    loadimage(&belt, StrToTchar(StrTexPath + "belt.png"));
    loadimage(&beltU, StrToTchar(StrTexPath + "beltU.png"));
    loadimage(&beltD, StrToTchar(StrTexPath + "beltD.png"));
    loadimage(&beltL, StrToTchar(StrTexPath + "beltL.png"));
    loadimage(&beltR, StrToTchar(StrTexPath + "beltR.png"));
    loadimage(&beltPU, StrToTchar(StrTexPath + "beltPU.png"));
    loadimage(&beltPD, StrToTchar(StrTexPath + "beltPD.png"));
    loadimage(&beltPL, StrToTchar(StrTexPath + "beltPL.png"));
    loadimage(&beltPR, StrToTchar(StrTexPath + "beltPR.png"));
    loadimage(&belti, StrToTchar(StrTexPath + "belti.png"));
    loadimage(&belC, StrToTchar(StrTexPath + "belC.png"));
    loadimage(&cutt, StrToTchar(StrTexPath + "cutt.png"));
    loadimage(&cuttU, StrToTchar(StrTexPath + "cuttU.png"));
    loadimage(&cuttD, StrToTchar(StrTexPath + "cuttD.png"));
    loadimage(&cuttL, StrToTchar(StrTexPath + "cuttL.png"));
    loadimage(&cuttR, StrToTchar(StrTexPath + "cuttR.png"));
    loadimage(&cutti, StrToTchar(StrTexPath + "cutti.png"));
    loadimage(&comp, StrToTchar(StrTexPath + "comp.png"));
    loadimage(&compU, StrToTchar(StrTexPath + "compU.png"));
    loadimage(&compD, StrToTchar(StrTexPath + "compD.png"));
    loadimage(&compL, StrToTchar(StrTexPath + "compL.png"));
    loadimage(&compR, StrToTchar(StrTexPath + "compR.png"));
    loadimage(&compi, StrToTchar(StrTexPath + "compi.png"));
    loadimage(&rota, StrToTchar(StrTexPath + "rota.png"));
    loadimage(&rotaU, StrToTchar(StrTexPath + "rotaU.png"));
    loadimage(&rotaD, StrToTchar(StrTexPath + "rotaD.png"));
    loadimage(&rotaL, StrToTchar(StrTexPath + "rotaL.png"));
    loadimage(&rotaR, StrToTchar(StrTexPath + "rotaR.png"));
    loadimage(&rotai, StrToTchar(StrTexPath + "rotai.png"));
    loadimage(&miner, StrToTchar(StrTexPath + "miner.png"));
    loadimage(&mineri, StrToTchar(StrTexPath + "mineri.png"));
    loadimage(&bin, StrToTchar(StrTexPath + "rubbishBin.png"));
    loadimage(&SqR, StrToTchar(StrTexPath + "squr-R.png"));
    loadimage(&SqY, StrToTchar(StrTexPath + "squr-Y.png"));
    loadimage(&SqB, StrToTchar(StrTexPath + "squr-B.png"));
    loadimage(&SqW, StrToTchar(StrTexPath + "squr-W.png"));
    loadimage(&SquI, StrToTchar(StrTexPath + "squr-uI.png"));
    loadimage(&SqnI, StrToTchar(StrTexPath + "squr-nI.png"));
    loadimage(&CcR, StrToTchar(StrTexPath + "ccle-R.png"));
    loadimage(&CcY, StrToTchar(StrTexPath + "ccle-Y.png"));
    loadimage(&CcB, StrToTchar(StrTexPath + "ccle-B.png"));
    loadimage(&CcW, StrToTchar(StrTexPath + "ccle-W.png"));
    loadimage(&CcuI, StrToTchar(StrTexPath + "ccle-uI.png"));
    loadimage(&CcnI, StrToTchar(StrTexPath + "ccle-nI.png"));
    loadimage(&MlR, StrToTchar(StrTexPath + "mill-R.png"));
    loadimage(&MlY, StrToTchar(StrTexPath + "mill-Y.png"));
    loadimage(&MlB, StrToTchar(StrTexPath + "mill-B.png"));
    loadimage(&MlW, StrToTchar(StrTexPath + "mill-W.png"));
    loadimage(&MluI, StrToTchar(StrTexPath + "mill-uI.png"));
    loadimage(&MlnI, StrToTchar(StrTexPath + "mill-nI.png"));
    loadimage(&shadowM, StrToTchar(StrTexPath + "shadowM.png"));
    loadimage(&shadowL, StrToTchar(StrTexPath + "shadowL.png"));
    loadimage(&shadowR, StrToTchar(StrTexPath + "shadowR.png"));
    loadimage(&shadowU, StrToTchar(StrTexPath + "shadowU.png"));
    loadimage(&shadowD, StrToTchar(StrTexPath + "shadowD.png"));
    loadimage(&shadowLU, StrToTchar(StrTexPath + "shadowLU.png"));
    loadimage(&shadowLD, StrToTchar(StrTexPath + "shadowLD.png"));
    loadimage(&shadowRU, StrToTchar(StrTexPath + "shadowRU.png"));
    loadimage(&shadowRD, StrToTchar(StrTexPath + "shadowRD.png"));
}

void putNumbers()
{
    std::wstringstream ssscore;
    ssscore << totalScore;
    outtextxy(669, 40, ssscore.str().c_str());
    ssscore.str(_T(""));
    std::wstringstream sstime;
    sstime << ((currentTime - startTime) / 1000.0 + 1000.0);
    outtextxy(534, 40, sstime.str().c_str());
    sstime.str(_T(""));
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
    for (int i = 0; i < 257; i++) {
        double scale = 1.0625;
        for (int j = 0; j < 11; j++) {
            scale -= 0.0625;
            float vscale = 1 / scale;
            mullist[i][j][0] = (int)((i)*vscale);
            mullist[i][j][1] = (int)((i)*vscale) * 64;
            mullist[i][j][2] = (int)(i * vscale) * 128;
            mullist[i][j][3] = (int)(i * vscale) * 192;
            mullist[i][j][4] = (int)(i * vscale) * 256;
        }
    }
}


void IntImg::putImg(int x, int y, IMAGE* srcimg, int direction = 1, double scale = 1) {
    DWORD* src = GetImageBuffer(srcimg);
    float vScale = 1 / scale;
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
            switch (direction) {
            case 1:i = (int)((iy - y) * vScale) * src_width + (ix - x) * vScale; break;
            case 2:i = (src_height - (int)((iy - y + 1) * vScale)) * src_width + src_width - 1 - (int)((ix - x) * vScale); break;
            case 3:i = (int)((ix - x) * vScale) * src_width + src_width - 1 - (int)(iy - y) * vScale; break;
            case 4:i = (src_width - (int)((ix - x + 1) * vScale)) * src_width + (int)((iy - y) * vScale); break;
            }
            i = (i < src_X && i >= 0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0) {
                if (sa == 255) {
                    pixel[ix][iy] = src[i];
                }
                else {
                    int sr = ((src[i] & 0xff0000) >> 16);
                    int sg = ((src[i] & 0xff00) >> 8);
                    int sb = src[i] & 0xff;
                    int dr = ((pixel[ix][iy] & 0xff0000) >> 16) * (255 - sa);
                    int dg = ((pixel[ix][iy] & 0xff00) >> 8) * (255 - sa);
                    int db = (pixel[ix][iy] & 0xff) * (255 - sa);
                    pixel[ix][iy] = ((sr + (dr >> 8)) << 16) | ((sg + (dg >> 8)) << 8) | (sb + (db >> 8));
                }
            }
        }
    }
}

void IntImg::putImg1(int x, int y, IMAGE* srcimg)
{
    DWORD* src = GetImageBuffer(srcimg);
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int src_X = src_width * src_height;
    int lx = (x > 0) ? x : 0;
    int ly = (y > 0) ? y : 0;
    int Mx = (x + src_width * screenScale > screenSizeX) ? screenSizeX : x + src_width * screenScale;
    int My = (y + src_height * screenScale > screenSizeY) ? screenSizeY : y + src_height * screenScale;
    int mul3 = src_width / 64;
    int i = 0;
    int scl = pScale;
    for (int iy = ly; iy < My; iy++) {
        for (int ix = lx; ix < Mx; ix++) {
            i = mullist[iy - y][scl][mul3] + mullist[ix - x][scl][0];
            i = (i < src_X && i >= 0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0) {
                if (sa == 255) {
                    pixel[ix][iy] = src[i];
                }
                else {
                    int sr = ((src[i] & 0xff0000) >> 16);
                    int sg = ((src[i] & 0xff00) >> 8);
                    int sb = src[i] & 0xff;
                    int dr = ((pixel[ix][iy] & 0xff0000) >> 16) * (255 - sa);
                    int dg = ((pixel[ix][iy] & 0xff00) >> 8) * (255 - sa);
                    int db = (pixel[ix][iy] & 0xff) * (255 - sa);
                    pixel[ix][iy] = ((sr + (dr >> 8)) << 16) | ((sg + (dg >> 8)) << 8) | (sb + (db >> 8));
                }
            }
        }
    }
}

void IntImg::putImg(int x, int y, double r, IMAGE* srcimg, double scale = 1)
{
    DWORD* src = GetImageBuffer(srcimg);
    float vScale = 1 / scale;
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
    center_width = scale * src_width / 2;
    center_height = scale * src_height / 2;
    int i = 0; int irx = 0; int iry = 0;
    int src_X = src_width * src_height;
    for (int iy = ly; iy < My; iy++) {
        for (int ix = lx; ix < Mx; ix++) {
            irx = (int)((ix - x - center_width) * cosr - (iy - y - center_height) * sinr + center_width);
            iry = (int)((iy - y - center_height) * cosr + (ix - x - center_width) * sinr + center_height);
            irx = (irx >= 0 && irx < src_width * scale) ? irx : 0;
            iry = (iry >= 0 && iry < src_height * scale) ? iry : 0;
            i = (int)(iry * vScale) * src_width + irx * vScale;
            i = (i < src_X && i >= 0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0) {
                if (sa == 255) {
                    pixel[ix][iy] = src[i];
                }
                else {
                    int sr = ((src[i] & 0xff0000) >> 16);
                    int sg = ((src[i] & 0xff00) >> 8);
                    int sb = src[i] & 0xff;
                    int dr = ((pixel[ix][iy] & 0xff0000) >> 16) * (255 - sa);
                    int dg = ((pixel[ix][iy] & 0xff00) >> 8) * (255 - sa);
                    int db = (pixel[ix][iy] & 0xff) * (255 - sa);
                    pixel[ix][iy] = ((sr + (dr >> 8)) << 16) | ((sg + (dg >> 8)) << 8) | (sb + (db >> 8));
                }
            }
        }
    }
}

void IntImg::putShadow(int x, int y, IMAGE* srcimg, double scale) {
    DWORD* src = GetImageBuffer(srcimg);
    float vScale = 1 / scale;
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int src_X = src_width * src_height;
    int lx = (x > 0) ? x : 0;
    int ly = (y > 0) ? y : 0;
    int Mx = (x + src_width * scale > screenSizeX) ? screenSizeX : x + src_width * scale;
    int My = (y + src_height * scale > screenSizeY) ? screenSizeY : y + src_height * scale;
    int i = 0;
    int scl = pScale;
    for (int iy = ly; iy < My; iy++) {
        for (int ix = lx; ix < Mx; ix++) {
            i = mullist[iy - y][scl][3] + mullist[ix - x][scl][0];
            i = (i < src_X && i >= 0) ? i : 0;
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0 && sa > shade[ix][iy]) {
                int psa = shade[ix][iy];
                float rt = (255.0 - sa) / (255.0 - psa);
                shade[ix][iy] = sa;
                int dr = ((pixel[ix][iy] & 0xff0000) >> 16) * rt;
                int dg = ((pixel[ix][iy] & 0xff00) >> 8) * rt;
                int db = (pixel[ix][iy] & 0xff) * rt;
                pixel[ix][iy] = (dr << 16) | (dg << 8) | db;

            }
        }
    }
}

void IntImg::RenderImg() {
    DWORD* dst = GetImageBuffer(NULL);
    for (int iy = 0; iy < screenSizeY; iy++) {
        for (int ix = 0; ix < screenSizeX; ix++) {
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

void IntImg::putGrounds() {
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &grnd, 1, screenScale);
        }
    }
}

void IntImg::putBuildings(World* world) {
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            if (world->mapp[i][j].type == BELTID) {
                switch (world->belt[world->mapp[i][j].id].dir) {
                case UP:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltU); break;
                case DOWN:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltD); break;
                case LEFT:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltL); break;
                case RIGHT:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltR); break;
                }
            }
        }
    }
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            switch (world->mapp[i][j].type)
            {
            case(BELTID):
                for (int bbf = 1; bbf < 4; bbf++) {
                    if (world->belt[world->mapp[i][j].id].idBef[bbf] != 0)
                        if (world->belt[world->belt[world->mapp[i][j].id].idBef[bbf]].dir != world->belt[world->mapp[i][j].id].dir)
                            switch (world->belt[world->belt[world->mapp[i][j].id].idBef[bbf]].dir) {
                            case UP:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltPD); break;
                            case DOWN:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltPU); break;
                            case LEFT:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltPR); break;
                            case RIGHT:putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &beltPL); break;
                            }
                }
                break;
            case(ROTATORID):
                switch (world->rotator[world->mapp[i][j].id].dir) {
                case UP:putImg((j * 64 - 32) * screenScale + cameraPositionX, (i - 1) * 64 * screenScale + cameraPositionY, &rotaU, 1, screenScale); break;
                case DOWN:putImg((j * 64 - 32) * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &rotaD, 1, screenScale); break;
                case LEFT:putImg((j - 1) * 64 * screenScale + cameraPositionX, (i * 64-32) * screenScale + cameraPositionY, &rotaL, 1, screenScale); break;
                case RIGHT:putImg(j * 64 * screenScale + cameraPositionX, (i * 64 - 32) * screenScale + cameraPositionY, &rotaR, 1, screenScale); break;
                }
                if(world->rotator[world->mapp[i][j].id].isMoved)
                    switch (world->rotator[world->mapp[i][j].id].dir) {
                    case UP:putImg((j * 64 ) * screenScale + cameraPositionX, (i * 64-32) * screenScale + cameraPositionY, &rotai, 1, screenScale); break;
                    case DOWN:putImg((j * 64) * screenScale + cameraPositionX, (i * 64+32) * screenScale + cameraPositionY, &rotai, 2, screenScale); break;
                    case LEFT:putImg((j * 64 - 32) * 64 * screenScale + cameraPositionX, (i * 64) * screenScale + cameraPositionY, &rotai, 3, screenScale); break;
                    case RIGHT:putImg((j * 64 + 32) * screenScale + cameraPositionX, (i * 64) * screenScale + cameraPositionY, &rotai, 4, screenScale); break;
                    }
                break;
            case(CUTTERID):
                if (world->mapp[i][j].isMain == true) {
                    switch (world->cutter[world->mapp[i][j].id].dir) {
                    case UP:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cuttU); break;
                    case DOWN:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cuttD); break;
                    case LEFT:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cuttL); break;
                    case RIGHT:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cuttR); break;
                    }
                    if (world->cutter[world->mapp[i][j].id].isMovedMain)
                        putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cutti, world->cutter[world->mapp[i][j].id].dir, screenScale);
                }
                break;

            case(COMPOSERID):
                if (world->mapp[i][j].isMain == true) {
                    switch (world->composer[world->mapp[i][j].id].dir) {
                    case UP:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compU); break;
                    case DOWN:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compD); break;
                    case LEFT:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compL); break;
                    case RIGHT:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compR); break;
                    }
                    if (world->composer[world->mapp[i][j].id].isMoved)
                        putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compi, world->composer[world->mapp[i][j].id].dir, screenScale);
                }
                break;
            }

        }
    }
}

void IntImg::putBuildings2(World* world) {
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            switch (world->mapp[i][j].type)
            {
            case(MINERID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &miner, world->miner[world->mapp[i][j].id].dir, screenScale);
                if (world->miner[world->mapp[i][j].id].isMoved)
                    putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &mineri, world->miner[world->mapp[i][j].id].dir, screenScale);
                break;
            case(RUBBISHBINID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &bin, UP, screenScale); break;
            }

        }
    }
}

void IntImg::putItems(World* world) {
    for (int i = 0; i < world->maxBeltId; i++) {
        {
            // The belt has item, start rendering
            Item itemRender = world->belt[i].itemPre;
            int y = world->belt[i].pos[0] * 64 * screenScale + cameraPositionY;
            int x = world->belt[i].pos[1] * 64 * screenScale + cameraPositionX;
            if (!world->belt[i].isStuck)
                switch (world->belt[i].dir) {
                case UP:y = y - tickRender * screenScale; break;
                case DOWN:y += tickRender * screenScale; break;
                case LEFT:x -= tickRender * screenScale; break;
                case RIGHT:x += tickRender * screenScale; break;
                }
            int dir;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; break;
                    case 1:dir = 4; break;
                    case 2:dir = 3; break;
                    case 3:dir = 2; break;
                    }
                    putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir);
                }
            }

        }
    }
    for (int i = 0; i < world->maxMinerId; i++) {
        if (world->miner[i].isMoved) {
            Item itemRender = world->miner[i].item;
            int y = world->miner[i].pos[0] * 64 * screenScale + cameraPositionY;
            int x = world->miner[i].pos[1] * 64 * screenScale + cameraPositionX;
            switch (world->miner[i].dir) {
            case UP:y = y - tickRender * screenScale; break;
            case DOWN:y += tickRender * screenScale; break;
            case LEFT:x -= tickRender * screenScale; break;
            case RIGHT:x += tickRender * screenScale; break;
            }
            int dir;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; break;
                    case 1:dir = 4; break;
                    case 2:dir = 3; break;
                    case 3:dir = 2; break;
                    }
                    putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir);
                }
            }

        }
    }
    for (int i = 0; i < world->maxCutterId; i++) {
        {
            Item itemRender = world->cutter[i].OutputMainPre;
            int y = world->cutter[i].pos[0] * 64 * screenScale + cameraPositionY;
            int x = world->cutter[i].pos[1] * 64 * screenScale + cameraPositionX;
            if (world->cutter[i].isMovedMain)
                switch (world->cutter[i].dir) {
                case UP:y = y - tickRender * screenScale; break;
                case DOWN:y += tickRender * screenScale; break;
                case LEFT:x -= tickRender * screenScale; break;
                case RIGHT:x += tickRender * screenScale; break;
                }
            int dir;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; break;
                    case 1:dir = 4; break;
                    case 2:dir = 3; break;
                    case 3:dir = 2; break;
                    }
                    putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir);
                }
            }

        }
        {
            Item itemRender = world->cutter[i].OutputSubPre;
            int y = world->cutter[i].pos[0] * 64 * screenScale + cameraPositionY;
            int x = world->cutter[i].pos[1] * 64 * screenScale + cameraPositionX;
            int yd = 0; int xd = 0;
            if (world->cutter[i].isMovedSub)
                switch (world->cutter[i].dir) {
                case UP:y = y - tickRender * screenScale; xd = tickRender * screenScale; break;
                case DOWN:y += tickRender * screenScale; xd = -tickRender * screenScale; break;
                case LEFT:x -= tickRender * screenScale; yd = -tickRender * screenScale; break;
                case RIGHT:x += tickRender * screenScale; yd = tickRender * screenScale; break;
                }
            int dir;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 1:dir = 4; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x + xd, y + yd, dir); break;
                    case 2:dir = 3; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 3:dir = 2; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x + xd, y + yd, dir); break;
                    }
                }
            }

        }
    }
    for (int i = 0; i < world->maxComposerId; i++) {
        {
            Item itemRender = world->composer[i].OutputPre;
            int y = world->composer[i].pos[0] * 64 * screenScale + cameraPositionY;
            int x = world->composer[i].pos[1] * 64 * screenScale + cameraPositionX;
            int yd = 0; int xd = 0;
            if (world->composer[i].isMoved)
                switch (world->composer[i].dir) {
                case UP:y -= tickRender * screenScale; xd = (64 - tickRender) * screenScale; break;
                case DOWN:y += tickRender * screenScale; xd = (tickRender - 64) * screenScale; break;
                case LEFT:x -= tickRender * screenScale; yd = (tickRender - 64) * screenScale; break;
                case RIGHT:x += tickRender * screenScale; yd = (64 - tickRender) * screenScale; break;
                }
            else
                switch (world->composer[i].dir) {
                case UP:xd = (64) * screenScale; break;
                case DOWN:xd = -(64) * screenScale; break;
                case RIGHT:yd = (64) * screenScale; break;
                }
            int dir;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 1:dir = 4; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x + xd, y + yd, dir); break;
                    case 2:dir = 3; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 3:dir = 2; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x + xd, y + yd, dir); break;
                    }
                }
            }

        }
    }
    for (int i = 0; i < world->maxRotatorId; i++) {
        {
            Item itemRender = world->rotator[i].OutputPre;
            int y = world->rotator[i].pos[0] * 64 * screenScale + cameraPositionY;
            int x = world->rotator[i].pos[1] * 64 * screenScale + cameraPositionX;
            int yd = 0; int xd = 0;
            if (world->rotator[i].isMoved)
                switch (world->rotator[i].dir) {
                case UP:y = y - tickRender * screenScale; break;
                case DOWN:y += tickRender * screenScale; break;
                case LEFT:x -= tickRender * screenScale; break;
                case RIGHT:x += tickRender * screenScale; break;
                }
            float r;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:r = 0; break;
                    case 1:r = -1.57; break;
                    case 2:r = 1.57; break;
                    case 3:r = 3.14; break;
                    }
                    int code = itemRender.shapeId[0][j][k] * 8 + itemRender.colorId[0][j][k];
                    if (world->rotator[i].isMoved)
                        r += (float)(32 - tickRender / 2) / 20.38;
                    else r += 1.57;
                    switch (code) {
                    case 9:
                        putImg(x, y,r, &CcR, screenScale); break;
                    case 10:
                        putImg(x, y,r, &CcY, screenScale); break;
                    case 11:
                        putImg(x, y,r, &CcB, screenScale); break;
                    case 12:
                        putImg(x, y,r, &CcW, screenScale); break;
                    case 17:
                        putImg(x, y,r, &SqR, screenScale); break;
                    case 18:
                        putImg(x, y,r, &SqY, screenScale); break;
                    case 19:
                        putImg(x, y,r, &SqB, screenScale); break;
                    case 20:
                        putImg(x, y,r, &SqW, screenScale); break;
                    case 25:
                        putImg(x, y,r, &MlR, screenScale); break;
                    case 26:
                        putImg(x, y,r, &MlY, screenScale); break;
                    case 27:
                        putImg(x, y,r, &MlB, screenScale); break;
                    case 28:
                        putImg(x, y,r, &MlW, screenScale); break;
                    }
                    //putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir);
                }
            }

        }
    }
}

void IntImg::putAnItem(int shape, int color, int x, int y, int dir)
{
    int code = shape * 8 + color;
    switch (code) {
    case 9:
        putImg(x, y, &CcR, dir, screenScale); break;
    case 10:
        putImg(x, y, &CcY, dir, screenScale); break;
    case 11:
        putImg(x, y, &CcB, dir, screenScale); break;
    case 12:
        putImg(x, y, &CcW, dir, screenScale); break;
    case 17:
        putImg(x, y, &SqR, dir, screenScale); break;
    case 18:
        putImg(x, y, &SqY, dir, screenScale); break;
    case 19:
        putImg(x, y, &SqB, dir, screenScale); break;
    case 20:
        putImg(x, y, &SqW, dir, screenScale); break;
    case 25:
        putImg(x, y, &MlR, dir, screenScale); break;
    case 26:
        putImg(x, y, &MlY, dir, screenScale); break;
    case 27:
        putImg(x, y, &MlB, dir, screenScale); break;
    case 28:
        putImg(x, y, &MlW, dir, screenScale); break;
    }
}

void IntImg::putUI() {
    int scrscl64 = screenScale * 64;
    int UIbX = ((mousePositionX - cameraPositionX) / scrscl64) * scrscl64 + cameraPositionX;
    int UIbY = ((mousePositionY - cameraPositionY) / scrscl64) * scrscl64 + cameraPositionY;
    switch (mouseCase) {
    case NORMALCASE: {
        putImg(mousePositionX - 32 * screenScale, mousePositionY - 32 * screenScale, mousePositionY / 14.5 - screenScale, &mouse1, screenScale);
        putImg(mousePositionX - 32 * (screenScale / 2 + 0.5), mousePositionY - 32 * (screenScale / 2 + 0.5), -mousePositionX / 28.5 + screenScale, &mouse2, screenScale / 2 + 0.5); break;
    }
    case UIBELT: putImg(UIbX - 32 * screenScale, UIbY - 32 * screenScale, &beltOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr1); putImg(43, 440, &UIBlight); break;
    case UICUTTER: putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &cuttOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr3); putImg(237, 440, &UIBlight); break;
    case UICOMPOSER: putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &compOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr3); putImg(334, 440, &UIBlight); break;
    case UIROTATOR: putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &rotaOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr2); putImg(140, 440, &UIBlight); break;
    case UIDELETER: putImg(UIbX, UIbY, &dstrOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr6); putImg(528, 440, &UIBlight); break;
    }
    putImg(0, 0, &UIframe1);
    putImg(0, 396, &UIframe2);
    putImg(43, 443, &UIbelt);
    putImg(140, 443, &UIrota);
    putImg(237, 443, &UIdivi);
    putImg(334, 443, &UIcomp);
    putImg(431, 443, &UIcolr);
    putImg(528, 443, &UIdes);
    switch (hoverCase) {
    case UIBELT:putImg(740, 435, &UIbdscr1); putImg(43, 440, &UIBlight); break;
    case UIROTATOR:putImg(740, 435, &UIbdscr2); putImg(140, 440, &UIBlight); break;
    case UICUTTER: putImg(740, 435, &UIbdscr3); putImg(237, 440, &UIBlight); break;
    case UICOMPOSER: putImg(740, 435, &UIbdscr4); putImg(334, 440, &UIBlight); break;
    case UICOLORER: putImg(740, 435, &UIbdscr5); putImg(431, 440, &UIBlight); break;
    case UIDELETER: putImg(740, 435, &UIbdscr6); putImg(528, 440, &UIBlight); break;
    case PAUSE: putImg(740, 435, &UIbdscrT); putImg(851, 15, &pauseBT); break;
    case SPEEDUP: putImg(740, 435, &UIbdscrE); putImg(772, 15, &speedBT); break;
    }
    if (mouseCase == NORMALCASE && hoverCase == NORMALCASE) { putImg(740, 435, &UIbdscr0); }
    if (preSpeedup) { putImg(772, 15, &speedBT2x); putImg(772, 15,tickRender/10.19, &speedBT2xR);}
    if (isPause) { putImg(380, 200, &pauseTX); putImg(851, 15, &pauseBT); }
}

void IntImg::blur() {
    int sum;
    int sr, sg, sb;
    int tr, tg, tb;
    int r = 6;
    for (int i = 45; i < screenSizeX - 235; i += 2) {
        for (int j = 442; j < screenSizeY - 4; j += 2) {
            tr = 0; tg = 0; tb = 0;
            for (int ir = -3; ir < 3; ir++) {
                for (int jr = -3; jr < 3; jr++) {
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

void IntImg::putIllum(World* world)
{
    for (int i = upBound + 1; i < dnBound - 1; i++) {
        for (int j = leftBound + 1; j < rightBound - 1; j++) {
            if (world->mapp[i][j].type != GROUNDID) {
                putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowM);
            }
            else {
                if (i < MAPLENGTH - 1)if (world->mapp[i + 1][j].type != 0) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowU);
                }
                if (j < MAPLENGTH - 1)if (world->mapp[i][j + 1].type != GROUNDID) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowL);
                }
                if (i > 1)if (world->mapp[i - 1][j].type != 0) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowD);
                }
                if (j > 1)if (world->mapp[i][j - 1].type != GROUNDID) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowR);
                }
                if (j > 1 && i > 1 && i < MAPLENGTH - 1 && j < MAPLENGTH - 1) {
                    if (world->mapp[i][j - 1].type == GROUNDID && world->mapp[i - 1][j].type == GROUNDID && world->mapp[i - 1][j - 1].type != GROUNDID) {
                        putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowRD);
                    }
                    if (world->mapp[i][j + 1].type == GROUNDID && world->mapp[i + 1][j].type == GROUNDID && world->mapp[i + 1][j + 1].type != GROUNDID) {
                        putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowLU);
                    }
                    if (world->mapp[i][j + 1].type == GROUNDID && world->mapp[i - 1][j].type == GROUNDID && world->mapp[i - 1][j + 1].type != GROUNDID) {
                        putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowLD);
                    }
                    if (world->mapp[i][j - 1].type == GROUNDID && world->mapp[i + 1][j].type == GROUNDID && world->mapp[i + 1][j - 1].type != GROUNDID) {
                        putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowRU);
                    }
                }
            }

        }
    }
}

void IntImg::renderTick(World* world) {
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
    putIllum(world);
    putBuildings(world);
    putItems(world);
    putBuildings2(world);
    blur();
    putUI();
    RenderImg();
    putNumbers();
}
