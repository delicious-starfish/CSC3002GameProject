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
IMAGE beltOO;
IMAGE cuttOO;
IMAGE compOO;
IMAGE dstrOO;
//Mouse
IMAGE mouse1;
IMAGE mouse2;
//Buildings
IMAGE grnd;
IMAGE belt;
IMAGE belti;
IMAGE belC;
IMAGE cutt;
IMAGE cutti;
IMAGE comp;
IMAGE compi;
IMAGE rota;
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
IMAGE shadow;


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

    loadimage(&UIframe1, StrToTchar(StrTexPath + "UI-02-up.png"));
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
    loadimage(&beltOO, StrToTchar(StrTexPath + "beltOO.png"));
    loadimage(&cuttOO, StrToTchar(StrTexPath + "cuttOO.png"));
    loadimage(&compOO, StrToTchar(StrTexPath + "compOO.png"));
    loadimage(&dstrOO, StrToTchar(StrTexPath + "dstrOO.png"));
    loadimage(&mouse1, StrToTchar(StrTexPath + "clickout.png"));
    loadimage(&mouse2, StrToTchar(StrTexPath + "clickin.png"));
    loadimage(&grnd, StrToTchar(StrTexPath + "grnd.png"));
    loadimage(&belt, StrToTchar(StrTexPath + "beltT1.png"));
    loadimage(&belti, StrToTchar(StrTexPath + "belti.png"));
    loadimage(&belC, StrToTchar(StrTexPath + "belC.png"));
    loadimage(&cutt, StrToTchar(StrTexPath + "cutt.png"));
    loadimage(&cutti, StrToTchar(StrTexPath + "cutti.png"));
    loadimage(&comp, StrToTchar(StrTexPath + "comp.png"));
    loadimage(&compi, StrToTchar(StrTexPath + "compi.png"));
    loadimage(&rota, StrToTchar(StrTexPath + "rota.png"));
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
    loadimage(&shadow, StrToTchar(StrTexPath + "shadow.png"));
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
    float vScale = 1 / scale;
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

void IntImg::putBuildings(World * world){
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            switch (world->mapp[i][j].type)
            {
            case(RUBBISHBINID)://No need to write anything here, it works
            case(ROTATORID):   //
            case(CUTTERID): if (!world->mapp[i][j].isMain)break;   //
            case(COMPOSERID):  //
            case(MINERID):     //
            case(BELTID):
                
                putShadow((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &shadow, screenScale); break;
            }
        }
    }
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            if (world->mapp[i][j].type == BELTID) {
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &belt, world->belt[world->mapp[i][j].id].dir, screenScale);
                if (world->belt[world->mapp[i][j].id].isMoved)
                    putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &belti, world->belt[world->mapp[i][j].id].dir, screenScale);
            }
        }
    }
    for (int i = upBound; i < dnBound; i++) {
        for (int j = leftBound; j < rightBound; j++) {
            switch (world->mapp[i][j].type)
            {
            case(ROTATORID):
                putImg(j * 64 * screenScale + cameraPositionX, i * 64 * screenScale + cameraPositionY, &rota, world->rotator[world->mapp[i][j].id].dir, screenScale); break;
            case(CUTTERID):
                if (world->mapp[i][j].isMain == true) {
                    putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cutt, world->cutter[world->mapp[i][j].id].dir, screenScale);
                    if (world->cutter[world->mapp[i][j].id].isMovedMain)
                        putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &cutti, world->cutter[world->mapp[i][j].id].dir, screenScale);
                }
                break;

            case(COMPOSERID):
                if (world->mapp[i][j].isMain == true) {
                    putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &comp, world->composer[world->mapp[i][j].id].dir, screenScale);
                    if (world->composer[world->mapp[i][j].id].isMoved)
                        putImg((j * 64 - 64) * screenScale + cameraPositionX, (i * 64 - 64) * screenScale + cameraPositionY, &compi, world->composer[world->mapp[i][j].id].dir, screenScale);
                }
                break;

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

void IntImg::putItems(World * world) {
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
                    putAnItem(itemRender.shapeId[0][j][k],itemRender.colorId[0][j][k], x, y, dir);
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
            case UP:y = y - tickRender * screenScale; xd = (64-tickRender) * screenScale; break;
            case DOWN:y += tickRender * screenScale; xd = tickRender * screenScale; break;
            case LEFT:x -= tickRender * screenScale; yd = tickRender * screenScale; break;
            case RIGHT:x += tickRender * screenScale; yd = (64 - tickRender) * screenScale; break;
            }
            else
                switch (world->composer[i].dir) {
                case UP:xd = (64) * screenScale; break;
                case RIGHT:yd = (64) * screenScale; break;
                }
            int dir;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    switch (2 * j + k) {
                    case 0:dir = 1; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 1:dir = 4; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x+xd, y+yd, dir); break;
                    case 2:dir = 3; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x, y, dir); break;
                    case 3:dir = 2; putAnItem(itemRender.shapeId[0][j][k], itemRender.colorId[0][j][k], x+xd, y+yd, dir); break;
                    }
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
        putImg(mousePositionX - 32 * screenScale, mousePositionY - 32 * screenScale, mousePositionY / 14.5 / screenScale, &mouse1, screenScale);
        putImg(mousePositionX - 32 * (screenScale / 2 + 0.5), mousePositionY - 32 * (screenScale / 2 + 0.5), -mousePositionX / 28.5 / screenScale, &mouse2, screenScale / 2 + 0.5); break;
    }
    case UIBELT: putImg(UIbX - 32 * screenScale, UIbY - 32 * screenScale, &beltOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr1); putImg(43, 440, &UIBlight); break;
    case UICUTTER: putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &cuttOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr3); putImg(237, 440, &UIBlight); break;
    case UICOMPOSER: putImg(UIbX - 64 * screenScale, UIbY - 64 * screenScale, &compOO, scrollCase, screenScale);
        putImg(740, 435, &UIbdscr3); putImg(334, 440, &UIBlight); break;
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
    }
    if (mouseCase == NORMALCASE && hoverCase == NORMALCASE) { putImg(740, 435, &UIbdscr0); }
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

void IntImg::renderTick(World * world) {
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
