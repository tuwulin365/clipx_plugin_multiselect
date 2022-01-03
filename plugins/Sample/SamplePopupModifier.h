#ifndef SAMPLE_POPUPMODIFIER_H
#define SAMPLE_POPUPMODIFIER_H

#include <ClipXPopupModifier.h>

class SamplePopupModifier : public ClipXPopupModifier
{
public:
    // called when clipx is constructing the system tray popup menu, add your items here
    virtual void customizeSystrayMenu(ClipXMenuHandler *menu);
    // called when clipx is constructing the clipboard history menu, add your items here
    virtual void customizeHistoryMenu(ClipXMenuHandler *menu, int is_hotkey, int is_submenu);
    // command callback for your popup items
    virtual void onCommand(int cmd);
    // custom drawing callbacks -- only called for items that had MF_OWNERDRAW specified
    virtual void onCustomSize(int cmd, int *w, int *h) {}
    virtual void onCustomDraw(int cmd, HDC dc, RECT rcitem, int state) {}
};

#endif
