#include "gameControl.h"
#include "gameCollection.h"
#include "gameRender.h"
#include "gameBuildings.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>



Button::Button(int lf, int rt, int up, int dn)
{
    lfBound = lf;
    rtBound = rt;
    upBound = up;
    dnBound = dn;
}

bool Button::isHover()
{
    if (mousePositionX >= lfBound 
        && mousePositionX <= rtBound 
        && mousePositionY >= upBound 
        && mousePositionY <= dnBound)
    { return true; }
    else { return false; }
}

void GameButton::operateTick(World * world,ExMessage& msg)
{
    if (BTbelt.isHover()) { hoverCase = UIBELT; }
    else if (BTrota.isHover()) { hoverCase = UIROTATOR; }
    else if (BTcutt.isHover()) { hoverCase = UICUTTER; }
    else if (BTcomp.isHover()) { hoverCase = UICOMPOSER; }
    else if (BTcolr.isHover()) { hoverCase = UICOLORER; }
    else if (BTdelete.isHover()) { hoverCase = UIDELETER; }
    else if (BTpause.isHover()) { hoverCase = PAUSE; } //pause
    else if (BTspeed.isHover()) { hoverCase = SPEEDUP; } //2X
    else { hoverCase = NORMALCASE; }
    //Check where is the mouse hovering currently
    int scrscl64 = screenScale * 64;
    int UIbX = ((mousePositionX - cameraPositionX) / scrscl64);
    int UIbY = ((mousePositionY - cameraPositionY) / scrscl64);
    //The location of mouse transfer into the location of mapp
    bool canBuild=false;
    //If the mouse does not hover above any button, it can build
    while (peekmessage(&msg, EM_MOUSE | EM_KEY))
    {
        //Mouse Operation
        switch (msg.message)
        {
        case WM_MOUSEMOVE:
            if (msg.lbutton) { cameraPositionX = msg.x - controlPositionX; cameraPositionY = msg.y - controlPositionY; }
            mousePositionX = msg.x; mousePositionY = msg.y;
            //Set the location of mouse
            break;
        case WM_LBUTTONDOWN:
            controlPositionX = msg.x - cameraPositionX; controlPositionY = msg.y - cameraPositionY;
            switch (hoverCase) {
            case PAUSE: //pause
                isPause ^= 1;
                break;
            case SPEEDUP: //2X
                preSpeedup ^= 1;
                break;
            }
            break;
        case WM_RBUTTONDOWN:
            switch (hoverCase) {
            case NORMALCASE:canBuild = true; break;
            case UICUTTER: 
            case UIROTATOR:
            case UICOMPOSER:
            case UIBELT: mouseCase = hoverCase; break;
            case UIDELETER: mouseCase = hoverCase; break;
            case PAUSE: //pause
                isPause ^= 1;
                break;
            case SPEEDUP: //2X
                preSpeedup ^= 1;
                break;
            }
            //Check where it hovers, and assign mouseCase when clicking right button
            if (canBuild)
                switch (mouseCase) {
                case NORMALCASE: break;
                case UICUTTER:
                case UIROTATOR:
                case UICOMPOSER:
                case UIBELT: world->buildAt(mouseCase - UIGROUND, UIbY, UIbX, scrollCase); mouseCase = NORMALCASE; break;
                case UIDELETER:
                    world->destroyAppendix(UIbY, UIbX);
                    world->destoryAt(UIbY, UIbX); mouseCase = NORMALCASE; break;
                }
            //If mouseCase is about to build, and canBuild, then build a building
            break;
        case WM_LBUTTONUP:
            break;
        case WM_MOUSEWHEEL:
            if (mouseCase == NORMALCASE) {
                if (msg.wheel > 0 && screenScale < 1) { screenScale += 0.0625; pScale--; }
                else if (msg.wheel < 0 && screenScale>0.375) { screenScale -= 0.0625; pScale++; }
            //Reset camera position to Realize mouse-centered scaling
            cameraPositionX = mousePositionX - (mousePositionX - cameraPositionX) * screenScale / previousScreenScale;
            cameraPositionY = mousePositionY - (mousePositionY - cameraPositionY) * screenScale / previousScreenScale;
            previousScreenScale = screenScale;
            }
            //Change screenscale by scrolling mouse
            if(mouseCase==UIBELT|| mouseCase == UIROTATOR || mouseCase == UICUTTER || mouseCase == UICOMPOSER) {
                if (msg.wheel < 0) {
                    switch (scrollCase) {
                    case UP:scrollCase = RIGHT; break;
                    case DOWN:scrollCase = LEFT; break;
                    case LEFT:scrollCase = UP; break;
                    case RIGHT:scrollCase = DOWN; break;
                    } }
                else if (msg.wheel > 0) {
                    switch (scrollCase) {
                    case UP:scrollCase = LEFT; break;
                    case DOWN:scrollCase = RIGHT; break;
                    case LEFT:scrollCase = DOWN; break;
                    case RIGHT:scrollCase = UP; break;
                    }
                }
            }//If it is to build, then scroll to rotate
            msg.wheel = 0;
            
            break;
        case WM_KEYDOWN:
            switch (msg.vkcode) {
            case VK_ESCAPE: break;
            case 0x52: //press R
                switch (scrollCase) {
                case UP:scrollCase = RIGHT; break;
                case DOWN:scrollCase = LEFT; break;
                case LEFT:scrollCase = UP; break;
                case RIGHT:scrollCase = DOWN; break;
                } break;
            }
            //stop
            break;
        }
    }
}