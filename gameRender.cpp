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
IMAGE menu1;
IMAGE menuIntro;
IMAGE menuFailed;
IMAGE menuSuccess;
IMAGE menuBTstart;
IMAGE menuBTsetting;
IMAGE UIframe1, UIframe2, UIframe3, UIframe4;
IMAGE UIbelt, UIdivi, UIrota, UIcolr, UIcomp, UIdes, UIacc;
IMAGE UIBlight;
IMAGE UIbdscr0, UIbdscr1, UIbdscr2, UIbdscr3, UIbdscr4, UIbdscr5, UIbdscr6, UIbdscr7;
IMAGE UIbdscrE, UIbdscrT, UIbdscrESC;
IMAGE UISCALER;
IMAGE UInumO;
IMAGE beltOO, cuttOO, compOO, rotaOO, dstrOO;
IMAGE pauseBT;
IMAGE speedBT;
IMAGE escBT;
IMAGE speedBT2x;
IMAGE speedBT2xR;
IMAGE pauseTX;
//Mouse
IMAGE mouse1;
IMAGE mouse2;
//Buildings
IMAGE grnd;
IMAGE belt, beltU, beltD, beltL, beltR, belti;
IMAGE beltPU, beltPD, beltPL, beltPR;
IMAGE belC;
IMAGE cutt, cuttU, cuttD, cuttL, cuttR, cutti;
IMAGE comp, compU, compD, compL, compR;
IMAGE compU2, compD2, compL2, compR2, compi;
IMAGE rota, rotaU, rotaD, rotaL, rotaR, rotai;
IMAGE miner, mineri;
IMAGE bin;
IMAGE acceptorPreview, acpt, acpti;

//Items
IMAGE SqR, SqY, SqB, SqW;
IMAGE SqRi, SqYi, SqBi, SqWi, SquI, SqnI;
IMAGE CcR, CcY, CcB, CcW;
IMAGE CcRi, CcYi, CcBi, CcWi, CcuI, CcnI;
IMAGE MlR, MlY, MlB, MlW;
IMAGE MlRi, MlYi, MlBi, MlWi, MluI, MlnI;
//Illum
IMAGE shadowM, shadowU, shadowL, shadowLU, shadowLD, shadowD, shadowRU, shadowRD, shadowR;
//Mask
IMAGE Mask1;
IMAGE clickMask;


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

    loadimage(&menu1, StrToTchar(StrTexPath + "menu1.png"));
    loadimage(&menuIntro, StrToTchar(StrTexPath + "Menu_Intro.png"));
    loadimage(&menuFailed, StrToTchar(StrTexPath + "Menu_Failed.png"));
    loadimage(&menuSuccess, StrToTchar(StrTexPath + "Menu_Success.png"));
    loadimage(&menuBTstart, StrToTchar(StrTexPath + "menuBTstart.png"));
    loadimage(&menuBTsetting, StrToTchar(StrTexPath + "menuBTsetting.png"));
    loadimage(&UIframe1, StrToTchar(StrTexPath + "UI-03-up.png"));
    loadimage(&UIframe2, StrToTchar(StrTexPath + "UI-02-dn.png"));
    loadimage(&UIframe3, StrToTchar(StrTexPath + "UI-01-lf.png"));
    loadimage(&UIframe4, StrToTchar(StrTexPath + "UI-01-rt.png"));
    loadimage(&UIbelt, StrToTchar(StrTexPath + "UI-Belt.png"));
    loadimage(&UIdivi, StrToTchar(StrTexPath + "UI-Divi.png"));
    loadimage(&UIcomp, StrToTchar(StrTexPath + "UI-Comp.png"));
    loadimage(&UIrota, StrToTchar(StrTexPath + "UI-Roto.png"));
    loadimage(&UIcolr, StrToTchar(StrTexPath + "UI-Colr.png"));
    loadimage(&UIdes, StrToTchar(StrTexPath + "UI-Dstr.png"));
    loadimage(&UIacc, StrToTchar(StrTexPath + "UI-Acc.png")); // Acceptor UI AWAITING ...
    loadimage(&UIBlight, StrToTchar(StrTexPath + "UI-Blight.png"));
    loadimage(&UIbdscr0, StrToTchar(StrTexPath + "UI-description0.png"));
    loadimage(&UIbdscr1, StrToTchar(StrTexPath + "UI-description1.png"));
    loadimage(&UIbdscr2, StrToTchar(StrTexPath + "UI-description2.png"));
    loadimage(&UIbdscr3, StrToTchar(StrTexPath + "UI-description3.png"));
    loadimage(&UIbdscr4, StrToTchar(StrTexPath + "UI-description4.png"));
    loadimage(&UIbdscr5, StrToTchar(StrTexPath + "UI-description5.png"));
    loadimage(&UIbdscr6, StrToTchar(StrTexPath + "UI-description6.png"));
    loadimage(&UIbdscr7, StrToTchar(StrTexPath + "UI-description7.png"));
    loadimage(&UIbdscrE, StrToTchar(StrTexPath + "UI-descriptionE.png"));
    loadimage(&UIbdscrT, StrToTchar(StrTexPath + "UI-descriptionT.png"));
    loadimage(&UIbdscrESC, StrToTchar(StrTexPath + "UI-descriptionESC.png"));
    loadimage(&UISCALER, StrToTchar(StrTexPath + "UI-SCALER2.png"));
    loadimage(&UInumO, StrToTchar(StrTexPath + "numO.png"));
    loadimage(&acceptorPreview, StrToTchar(StrTexPath + "acptOO.png"));
    loadimage(&beltOO, StrToTchar(StrTexPath + "beltOO.png"));
    loadimage(&cuttOO, StrToTchar(StrTexPath + "cuttOO.png"));
    loadimage(&compOO, StrToTchar(StrTexPath + "compOO.png"));
    loadimage(&rotaOO, StrToTchar(StrTexPath + "rotaOO.png"));
    loadimage(&dstrOO, StrToTchar(StrTexPath + "dstrOO.png"));
    loadimage(&pauseBT, StrToTchar(StrTexPath + "UI-pauseBT.png"));
    loadimage(&speedBT, StrToTchar(StrTexPath + "UI-speedBT.png"));
    loadimage(&escBT, StrToTchar(StrTexPath + "UI-esc.png"));
    loadimage(&speedBT2x, StrToTchar(StrTexPath + "UI-speedBT2x.png"));
    loadimage(&speedBT2xR, StrToTchar(StrTexPath + "UI-speedBT2x-R.png"));
    loadimage(&pauseTX, StrToTchar(StrTexPath + "UI-pause.png"));
    loadimage(&mouse1, StrToTchar(StrTexPath + "clickout.png"));
    loadimage(&mouse2, StrToTchar(StrTexPath + "clickin.png"));
    loadimage(&grnd, StrToTchar(StrTexPath + "grnd.png"));
    loadimage(&acpt, StrToTchar(StrTexPath + "acpt.png"));
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
    loadimage(&compU2, StrToTchar(StrTexPath + "compU2.png"));
    loadimage(&compD2, StrToTchar(StrTexPath + "compD2.png"));
    loadimage(&compL2, StrToTchar(StrTexPath + "compL2.png"));
    loadimage(&compR2, StrToTchar(StrTexPath + "compR2.png"));
    loadimage(&compi, StrToTchar(StrTexPath + "compi.png"));
    loadimage(&rota, StrToTchar(StrTexPath + "rota.png"));
    loadimage(&rotaU, StrToTchar(StrTexPath + "rotaU.png"));
    loadimage(&rotaD, StrToTchar(StrTexPath + "rotaD.png"));
    loadimage(&rotaL, StrToTchar(StrTexPath + "rotaL.png"));
    loadimage(&rotaR, StrToTchar(StrTexPath + "rotaR.png"));
    loadimage(&rotai, StrToTchar(StrTexPath + "rotai.png"));
    loadimage(&miner, StrToTchar(StrTexPath + "miner.png"));
    loadimage(&mineri, StrToTchar(StrTexPath + "mineri.png"));
    loadimage(&acpti, StrToTchar(StrTexPath + "acpti.png"));
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
    loadimage(&MlnI, StrToTchar(StrTexPath + "mill-nI.png"));
    loadimage(&SqRi, StrToTchar(StrTexPath + "squr-Ri.png"));
    loadimage(&SqYi, StrToTchar(StrTexPath + "squr-Yi.png"));
    loadimage(&SqBi, StrToTchar(StrTexPath + "squr-Bi.png"));
    loadimage(&SqWi, StrToTchar(StrTexPath + "squr-Wi.png"));
    loadimage(&CcRi, StrToTchar(StrTexPath + "ccle-Ri.png"));
    loadimage(&CcYi, StrToTchar(StrTexPath + "ccle-Yi.png"));
    loadimage(&CcBi, StrToTchar(StrTexPath + "ccle-Bi.png"));
    loadimage(&CcWi, StrToTchar(StrTexPath + "ccle-Wi.png"));
    loadimage(&MlRi, StrToTchar(StrTexPath + "mill-Ri.png"));
    loadimage(&MlYi, StrToTchar(StrTexPath + "mill-Yi.png"));
    loadimage(&MlBi, StrToTchar(StrTexPath + "mill-Bi.png"));
    loadimage(&MlWi, StrToTchar(StrTexPath + "mill-Wi.png"));
    loadimage(&shadowM, StrToTchar(StrTexPath + "shadowM.png"));
    loadimage(&shadowL, StrToTchar(StrTexPath + "shadowL.png"));
    loadimage(&shadowR, StrToTchar(StrTexPath + "shadowR.png"));
    loadimage(&shadowU, StrToTchar(StrTexPath + "shadowU.png"));
    loadimage(&shadowD, StrToTchar(StrTexPath + "shadowD.png"));
    loadimage(&shadowLU, StrToTchar(StrTexPath + "shadowLU.png"));
    loadimage(&shadowLD, StrToTchar(StrTexPath + "shadowLD.png"));
    loadimage(&shadowRU, StrToTchar(StrTexPath + "shadowRU.png"));
    loadimage(&shadowRD, StrToTchar(StrTexPath + "shadowRD.png"));
    loadimage(&Mask1, StrToTchar(StrTexPath + "MASK1.png"));
    loadimage(&clickMask, StrToTchar(StrTexPath + "clickMASK.png"));
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

void IntImg::putmskImg(int x, int y, double r, IMAGE* srcimg)
{
    DWORD* src = GetImageBuffer(srcimg);
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    float cosr = cos(r);
    float sinr = sin(r);
    int center_width;
    int center_height;
    int lx = (x > 0) ? x : 0;
    int ly = (y > 0) ? y : 0;
    int Mx = (x + src_width > screenSizeX) ? screenSizeX : x + src_width;
    int My = (y + src_height > screenSizeY) ? screenSizeY : y + src_height;
    center_width = src_width / 2;
    center_height = src_height / 2;
    int i = 0; int irx = 0; int iry = 0;
    int src_X = src_width * src_height;
    for (int iy = ly; iy < My; iy++) {
        for (int ix = lx; ix < Mx; ix++) {
            irx = (int)((ix - x - center_width) * cosr - (iy - y - center_height) * sinr + center_width);
            iry = (int)((iy - y - center_height) * cosr + (ix - x - center_width) * sinr + center_height);
            irx = (irx >= 0 && irx < src_width) ? irx : 0;
            iry = (iry >= 0 && iry < src_height) ? iry : 0;
            i = (int)(iry)*src_width + irx;
            i = (i < src_X && i >= 0) ? i : 0;
            int mskR = ((mask[ix][iy] & 0xff0000) >> 16);
            int sa = ((src[i] & 0xff000000) >> 24);
            if (mskR != 255) {
                sa = sa * (mskR / 390.0);
                if (sa != 0) {
                    if (sa == 255) pixel[ix][iy] = src[i];
                    else {
                        int sr = ((src[i] & 0xff0000) >> 16) * sa; int sg = ((src[i] & 0xff00) >> 8) * sa; int sb = (src[i] & 0xff) * sa;
                        int dr = ((pixel[ix][iy] & 0xff0000) >> 16) * (255 - sa); int dg = ((pixel[ix][iy] & 0xff00) >> 8) * (255 - sa);
                        int db = (pixel[ix][iy] & 0xff) * (255 - sa); pixel[ix][iy] = (((sr + dr) >> 8) << 16) | (((sg + dg) >> 8) << 8) | ((sb + db) >> 8);
                    }
                }
            }else{
                if (sa != 0) {
                    if (sa == 255) pixel[ix][iy] = src[i];
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
}


void IntImg::loadMask()
{
    IMAGE* srcimg = &Mask1;
    DWORD* src = GetImageBuffer(srcimg);
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int i = 0;
    for (int iy = 0; iy < src_height; iy++) {
        for (int ix = 0; ix < src_width; ix++) {
            i = (int)iy * src_width + ix;
            mask[ix][iy] = src[i];
        }
    }
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
            mask[ix][iy] = 0;
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
    dScale = 1;
    dScore = 0;
    dTen = 0;
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
            pixel[ix][iy] = 14974274;
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
                case LEFT:putImg((j - 1) * 64 * screenScale + cameraPositionX, (i * 64 - 32) * screenScale + cameraPositionY, &rotaL, 1, screenScale); break;
                case RIGHT:putImg(j * 64 * screenScale + cameraPositionX, (i * 64 - 32) * screenScale + cameraPositionY, &rotaR, 1, screenScale); break;
                }
                if (world->rotator[world->mapp[i][j].id].isMoved)
                    switch (world->rotator[world->mapp[i][j].id].dir) {
                    case UP:putImg((j * 64) * screenScale + cameraPositionX, (i * 64 - 32) * screenScale + cameraPositionY, &rotai, 1, screenScale); break;
                    case DOWN:putImg((j * 64) * screenScale + cameraPositionX, (i * 64 + 32) * screenScale + cameraPositionY, &rotai, 2, screenScale); break;
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
            case(COMPOSERID):
                if (world->mapp[i][j].isMain == true) {
                    switch (world->composer[world->mapp[i][j].id].dir) {
                    case UP:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compU2); break;
                    case DOWN:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compD2); break;
                    case LEFT:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compL2); break;
                    case RIGHT:putImg1((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compR2); break;
                    }
                    if (world->composer[world->mapp[i][j].id].isMoved)
                        putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compi, world->composer[world->mapp[i][j].id].dir, screenScale);
                }
                break;
            case (ACCEPTORID):
                if (world->mapp[i][j].isMain) {
                    // Render the Acceptor using acceptorImg
                    putImg1((j * 64-96) * screenScale + cameraPositionX, (i * 64-96) * screenScale + cameraPositionY, &acpt);

                    // If Acceptor has stored items, render them
                    if (true) {
                        Item storedItem = world->acceptor[world->mapp[i][j].id].target1;
                        // Render storedItem at center
                        // Using storedItem method to get item images
                        int dir;
                        int x = j * 64 * screenScale + cameraPositionX;
                        int y = i * 64 * screenScale + cameraPositionY;
                        for (int m = 0; m < 2; m++) {
                            for (int n = 0; n < 2; n++) {
                                switch (2 * m + n) {
                                case 0:dir = 1; break;
                                case 1:dir = 4; break;
                                case 2:dir = 3; break;
                                case 3:dir = 2; break;
                                }
                                //putAnItem(storedItem.shapeId[0][m][n], storedItem.colorId[0][m][n], j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, dir);
                                int code = storedItem.shapeId[0][m][n] * 8 + storedItem.colorId[0][m][n];
                                switch (code) {
                                case 9:
                                    putImg(x, y, &CcRi, dir, screenScale); break;
                                case 10:
                                    putImg(x, y, &CcYi, dir, screenScale); break;
                                case 11:
                                    putImg(x, y, &CcBi, dir, screenScale); break;
                                case 12:
                                    putImg(x, y, &CcWi, dir, screenScale); break;
                                case 17:
                                    putImg(x, y, &SqRi, dir, screenScale); break;
                                case 18:
                                    putImg(x, y, &SqYi, dir, screenScale); break;
                                case 19:
                                    putImg(x, y, &SqBi, dir, screenScale); break;
                                case 20:
                                    putImg(x, y, &SqWi, dir, screenScale); break;
                                case 25:
                                    putImg(x, y, &MlRi, dir, screenScale); break;
                                case 26:
                                    putImg(x, y, &MlYi, dir, screenScale); break;
                                case 27:
                                    putImg(x, y, &MlBi, dir, screenScale); break;
                                case 28:
                                    putImg(x, y, &MlWi, dir, screenScale); break;
                                }
                            }
                        }
                        if (world->acceptor[world->mapp[i][j].id].isMoved)
                            putImg1((j * 64 - 96) * screenScale + cameraPositionX, (i * 64 - 96) * screenScale + cameraPositionY, &acpti);
                    }
                }
                break;
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
            bool isHorizontal = (world->cutter[i].dir == LEFT || world->cutter[i].dir == RIGHT);
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    if(isHorizontal)
                    switch (2 * j + k) {
                    case 0:dir = 1; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 1:dir = 4; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 2:dir = 3; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x + xd, y + yd, dir); break;
                    case 3:dir = 2; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x + xd, y + yd, dir); break;
                    }
                    else
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
            if(world->composer[i].isMoved)
            switch (world->composer[i].dir) {
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
                        putImg(x, y, r, &CcR, screenScale); break;
                    case 10:
                        putImg(x, y, r, &CcY, screenScale); break;
                    case 11:
                        putImg(x, y, r, &CcB, screenScale); break;
                    case 12:
                        putImg(x, y, r, &CcW, screenScale); break;
                    case 17:
                        putImg(x, y, r, &SqR, screenScale); break;
                    case 18:
                        putImg(x, y, r, &SqY, screenScale); break;
                    case 19:
                        putImg(x, y, r, &SqB, screenScale); break;
                    case 20:
                        putImg(x, y, r, &SqW, screenScale); break;
                    case 25:
                        putImg(x, y, r, &MlR, screenScale); break;
                    case 26:
                        putImg(x, y, r, &MlY, screenScale); break;
                    case 27:
                        putImg(x, y, r, &MlB, screenScale); break;
                    case 28:
                        putImg(x, y, r, &MlW, screenScale); break;
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
    if (dir == 1)
        switch (code) {
        case 9:
        case 10:
        case 11:
        case 12:
            putImg1(x, y, &CcuI); break;
        case 17:
        case 18:
        case 19:
        case 20:
            putImg1(x, y, &SquI); break;
        case 25:
        case 26:
        case 27:
        case 28:
            putImg1(x, y, &MluI); break;
        }
    if (dir == 2)
        switch (code) {
        case 9:
        case 10:
        case 11:
        case 12:
            putImg1(x, y, &CcnI); break;
        case 17:
        case 18:
        case 19:
        case 20:
            putImg1(x, y, &SqnI); break;
        case 25:
        case 26:
        case 27:
        case 28:
            putImg1(x, y, &MlnI); break;
        }
}

void IntImg::putUI() {
    int scrscl64 = screenScale * 64;
    int UIbX = ((mousePositionX - cameraPositionX) / scrscl64) * scrscl64 + cameraPositionX;
    int UIbY = ((mousePositionY - cameraPositionY) / scrscl64) * scrscl64 + cameraPositionY;
    switch (mouseCase) {
    case NORMALCASE: {
        putImg(mousePositionX - 32 * screenScale, mousePositionY - 32 * screenScale, mousePositionY / 28.5 / dScale, &mouse1, screenScale);
        putImg(mousePositionX - 32 * (screenScale / 2 + 0.5), mousePositionY - 32 * (screenScale / 2 + 0.5), -mousePositionX / 43.5 / dScale, &mouse2, screenScale / 2 + 0.5); break;
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
    case UICOLORER:putImg(UIbX, UIbY, &bin, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr5); putImg(528, 440, &UIBlight); break;
    case UIACCEPTOR:
        // Render Acceptor preview (3x3 grid)
            // Use the acceptor preview image
        putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &acceptorPreview, 1, screenScale); // Direction is irrelevant since non-rotatable
        putImg(740, 435, &UIbdscr7); // Acceptor UI DESC AWAITING ...
        putImg(625, 440, &UIBlight);
        break;
    }
    blur();
    putImg(0, 0, &UIframe3);
    putImg(900, 0, &UIframe4);
    putImg(0, 0, &UIframe1);
    putImg(0, 396, &UIframe2);
    putImg(43, 443, &UIbelt);
    putImg(140, 443, &UIrota);
    putImg(237, 443, &UIdivi);
    putImg(334, 443, &UIcomp);
    putImg(431, 443, &UIcolr);
    putImg(528, 443, &UIdes);
    putImg(625, 443, &UIacc);
    putmskImg(-430, 0, dScale * 3.14 - 2.15, &UISCALER);
    putmskImg(534, 11, (((int)(startTime - currentTime)) / 100000) * 0.628, &UInumO);
    putmskImg(547, 11, dTen*0.628, &UInumO);
    putmskImg(560, 11, -sqrt((((int)(startTime - currentTime)) / 1000) * 0.628 - (startTime - currentTime) * 0.0006283)+ (((int)(startTime - currentTime)) / 1000) * 0.628, &UInumO);
    putmskImg(573, 11, (startTime - currentTime)*0.00628, &UInumO);
    putmskImg(682, 11, -(totalScore/10)*0.628, &UInumO);
    putmskImg(695, 11, -dScore*0.628, &UInumO);
    switch (hoverCase) {
    case UIBELT:putImg(740, 435, &UIbdscr1); putImg(43, 440, &UIBlight); break;
    case UIROTATOR:putImg(740, 435, &UIbdscr2); putImg(140, 440, &UIBlight); break;
    case UICUTTER: putImg(740, 435, &UIbdscr3); putImg(237, 440, &UIBlight); break;
    case UICOMPOSER: putImg(740, 435, &UIbdscr4); putImg(334, 440, &UIBlight); break;
    case UICOLORER: putImg(740, 435, &UIbdscr5); putImg(431, 440, &UIBlight); break;
    case UIDELETER: putImg(740, 435, &UIbdscr6); putImg(528, 440, &UIBlight); break;
    case UIACCEPTOR:
        // ACCEPTOR: TO BE RE-ADJUSTED
        putImg(740, 435, &UIbdscr7); // Adjust description image
        putImg(625, 440, &UIBlight); // need adjustment
        break;
    case PAUSE: putImg(740, 435, &UIbdscrT); putImg(851, 15, &pauseBT); break;
    case SPEEDUP: putImg(740, 435, &UIbdscrE); putImg(772, 15, &speedBT); break;
    case QUIT: putImg(740, 435, &UIbdscrESC); putImg(0, 0, &escBT); break;
    }
    if (mouseCase == NORMALCASE && hoverCase == NORMALCASE) { putImg(740, 435, &UIbdscr0); }
    if (preSpeedup) { putImg(772, 15, &speedBT2x); putImg(772, 15, tickRender / 10.19, &speedBT2xR); }
    if (isPause) { putImg(380, 200, &pauseTX); putImg(851, 15, &pauseBT); }
}

void IntImg::blur() {
    int sum;
    int sr, sg, sb;
    int tr, tg, tb;
    int r = 8;
    int mskR, mskG, mskB;
    for (int i = 1; i < screenSizeX - 8; i += 2) {
        for (int j = 1; j < screenSizeY - 8; j += 2) {
            mskR = ((mask[i][j] & 0xff0000) >> 16);
            mskG = ((mask[i][j] & 0xff00) >> 8);
            mskB = (mask[i][j] & 0xff);
            if (mskG < 255)if (mskB < 252 || !isPause)continue;
            if (mskR == 0)continue;
            tr = 0; tg = 0; tb = 0;


            if (mskR > 192) {
                for (int ir = -8; ir < 8; ir++) {
                    tr = tr + ((pixel[i + ir][j + ir] & 0xff0000) >> 16) + ((pixel[i + ir][j - ir] & 0xff0000) >> 16);
                    tg = tg + ((pixel[i + ir][j + ir] & 0xff00) >> 8) + ((pixel[i + ir][j - ir] & 0xff00) >> 8);
                    tb = tb + (pixel[i + ir][j + ir] & 0xff) + (pixel[i + ir][j - ir] & 0xff);
                }
                sr = tr >> 5;
                sg = tg >> 5;
                sb = tb >> 5;
                sum = (sr << 16) | (sg << 8) | (sb);
            }
            else if (mskR > 160) {
                for (int ir = -4; ir < 4; ir++) {
                    tr = tr + ((pixel[i + ir][j + ir] & 0xff0000) >> 16) + ((pixel[i + ir][j - ir] & 0xff0000) >> 16);
                    tg = tg + ((pixel[i + ir][j + ir] & 0xff00) >> 8) + ((pixel[i + ir][j - ir] & 0xff00) >> 8);
                    tb = tb + (pixel[i + ir][j + ir] & 0xff) + (pixel[i + ir][j - ir] & 0xff);
                }
                sr = tr >> 4;
                sg = tg >> 4;
                sb = tb >> 4;
                sum = (sr << 16) | (sg << 8) | (sb);
            }
            else if (mskR > 128) {
                for (int ir = -2; ir < 2; ir++) {
                    tr = tr + ((pixel[i + ir][j + ir] & 0xff0000) >> 16) + ((pixel[i + ir][j - ir] & 0xff0000) >> 16);
                    tg = tg + ((pixel[i + ir][j + ir] & 0xff00) >> 8) + ((pixel[i + ir][j - ir] & 0xff00) >> 8);
                    tb = tb + (pixel[i + ir][j + ir] & 0xff) + (pixel[i + ir][j - ir] & 0xff);
                }
                sr = tr >> 3;
                sg = tg >> 3;
                sb = tb >> 3;
                sum = (sr << 16) | (sg << 8) | (sb);
            }
            else {
                sum = pixel[i][j];
            }
            pixel[i][j] = sum; pixel[i + 1][j] = sum;
            pixel[i][j + 1] = sum; pixel[i + 1][j + 1] = sum;
        }
    }
}

void IntImg::putIllum(World* world)
{
    for (int i = upBound; i < dnBound; i++) {
        if (i<1 || i>MAPLENGTH - 1)continue;
        for (int j = leftBound; j < rightBound; j++) {
            if (j < 1 || j >= MAPLENGTH - 1)continue;
            if (world->mapp[i][j].type != GROUNDID && world->mapp[i][j].isMain) {
                putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowM);
            }
            else {
                if (world->mapp[i + 1][j].type != GROUNDID && world->mapp[i+1][j].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowU);
                }
                if (world->mapp[i][j + 1].type != GROUNDID && world->mapp[i][j+1].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowL);
                }
                if (world->mapp[i - 1][j].type != GROUNDID && world->mapp[i-1][j].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowD);
                }
                if (world->mapp[i][j - 1].type != GROUNDID && world->mapp[i][j-1].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowR);
                }
                if (!world->mapp[i][j - 1].isMain && !world->mapp[i - 1][j].isMain && world->mapp[i - 1][j - 1].type != GROUNDID && world->mapp[i-1][j-1].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowRD);
                }
                if (!world->mapp[i][j + 1].isMain && !world->mapp[i + 1][j].isMain && world->mapp[i + 1][j + 1].type != GROUNDID && world->mapp[i+1][j+1].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowLU);
                }
                if (!world->mapp[i][j + 1].isMain && !world->mapp[i - 1][j].isMain && world->mapp[i - 1][j + 1].type != GROUNDID && world->mapp[i-1][j+1].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowLD);
                }
                if (!world->mapp[i][j - 1].isMain && !world->mapp[i + 1][j].isMain && world->mapp[i + 1][j - 1].type != GROUNDID && world->mapp[i+1][j-1].isMain) {
                    putImg1(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &shadowRU);
                }
            }
        }
    }
}

void IntImg::renderTick(World* world) {
    ClearImg();
    dScale += (screenScale - dScale) / 4;
    dScore += (totalScore - dScore) / 8.0;
    dTen += ((((int)(startTime - currentTime-1000)) / 10000) - dTen) / 8.0;
    leftBound = -cameraPositionX / 64 / screenScale - 1;
    rightBound = (-cameraPositionX + screenSizeX + 64) / screenScale / 64 + 1;
    upBound = -cameraPositionY / 64 / screenScale - 1;
    dnBound = (-cameraPositionY + screenSizeY + 64) / screenScale / 64 + 1;
    leftBound = (leftBound < 0) ? 0 : leftBound;
    rightBound = (rightBound > MAPLENGTH) ? MAPLENGTH : rightBound;
    upBound = (upBound < 0) ? 0 : upBound;
    dnBound = (dnBound > MAPLENGTH) ? MAPLENGTH : dnBound;
    putGrounds();
    putIllum(world);
    putBuildings(world);
    putItems(world);
    putBuildings2(world);
    putUI();
    RenderImg();
}

void IntImg::renderMenu()
{
    putImg(0, 0, &menu1, 1, 1);
    if (hoverCase == MENUSTART)
        putImg(288, 299, &menuBTstart, 1, 1);
    if (hoverCase == MENUSETTING)
        putImg(288, 399, &menuBTsetting, 1, 1);
    RenderImg();
}

void IntImg::renderIntro() {
    putImg(0, 0, &menuIntro, 1, 1);
    if(hoverCase==QUIT)
        putImg(0, 0, &escBT);
    RenderImg();
}

void IntImg :: renderMenuFailed() {
    putImg(0, 0, &menuFailed, 1, 1);
    if (hoverCase == MENUSTART)
        putImg(288, 299, &menuBTstart, 1, 1);
    if (hoverCase == MENUSETTING)
        putImg(288, 399, &menuBTsetting, 1, 1);
    RenderImg();
}
void IntImg::renderMenuSuccess() {
    putImg(0, 0, &menuSuccess, 1, 1);
    if (hoverCase == MENUSTART)
        putImg(288, 299, &menuBTstart, 1, 1);
    if (hoverCase == MENUSETTING)
        putImg(288, 399, &menuBTsetting, 1, 1);
    RenderImg();
}
