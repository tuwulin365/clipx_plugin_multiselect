#ifndef CLIPX_POPUPMODIFIER_H
#define CLIPX_POPUPMODIFIER_H

// CLIPX PLUGIN SDK - DO NOT MODIFY

#include <bfc/dispatch.h>

class ClipXMenuHandler;

class svc_ClipXPopupModifier : public Dispatchable {
protected:
  svc_ClipXPopupModifier() {}
  virtual ~svc_ClipXPopupModifier() {}

public:
  static GUID getServiceType() { GUID g = SVCTGUID_MK4CC('c','x','0','4'); return g; }
  static const char *getServiceName() { return "ClipX Popup Modifier Service"; }
  void customizeSystrayMenu(ClipXMenuHandler *menu) { _voidcall(SVC_CLIPX_POPUPMODIFIER_CUSTOMIZESYSTRAY, menu); }
  void customizeHistoryMenu(ClipXMenuHandler *menu, int is_hotkey, int is_submenu) { _voidcall(SVC_CLIPX_POPUPMODIFIER_CUSTOMIZEHISTORY, menu, is_hotkey, is_submenu); }
  void onCustomSize(int cmd, int *w, int *h) { _voidcall(SVC_CLIPX_POPUPMODIFIER_ONCUSTOMSIZE, cmd, w, h); }
  void onCustomDraw(int cmd, HDC dc, RECT rcitem, int state) { _voidcall(SVC_CLIPX_POPUPMODIFIER_ONCUSTOMDRAW, cmd, dc, rcitem, state); }
  int onCustomAccelerator(char c) { return _call(SVC_CLIPX_POPUPMODIFIER_ONCUSTOMACCELERATOR, -1, c); }
  void onCommand(int cmd) { _voidcall(SVC_CLIPX_POPUPMODIFIER_ONCOMMAND, cmd); }
  void onDeleteMenu(ClipXMenuHandler *menu) { _voidcall(SVC_CLIPX_POPUPMODIFIER_ONDELETEMENU, menu); }

  enum {
    SVC_CLIPX_POPUPMODIFIER_CUSTOMIZESYSTRAY    = 10,
    SVC_CLIPX_POPUPMODIFIER_CUSTOMIZEHISTORY    = 20,
    SVC_CLIPX_POPUPMODIFIER_ONCOMMAND           = 30,
    SVC_CLIPX_POPUPMODIFIER_ONCUSTOMSIZE        = 40,
    SVC_CLIPX_POPUPMODIFIER_ONCUSTOMDRAW        = 50,
    SVC_CLIPX_POPUPMODIFIER_ONCUSTOMACCELERATOR = 60,
    SVC_CLIPX_POPUPMODIFIER_ONDELETEMENU        = 70,
  };
};

class ClipXPopupModifierI : public svc_ClipXPopupModifier {
protected:
  ClipXPopupModifierI() {}
  virtual ~ClipXPopupModifierI() {}

public:
  virtual void customizeSystrayMenu(ClipXMenuHandler *menu)=0;
  virtual void customizeHistoryMenu(ClipXMenuHandler *menu, int is_hotkey, int is_submenu)=0;
  virtual void onCustomSize(int cmd, int *w, int *h)=0;
  virtual void onCustomDraw(int cmd, HDC dc, RECT rcitem, int state)=0;
  virtual int onCustomAccelerator(char c)=0;
  virtual void onCommand(int cmd)=0;
  virtual void onDeleteMenu(ClipXMenuHandler *menu)=0;

protected:
  RECVS_DISPATCH;
};

#include <api/service/servicei.h>
template <class T>
class ClipXPopupModifierCreator : public waServiceFactoryTSingle<svc_ClipXPopupModifier, T> {};

#include <api/service/svcenumt.h>

class svc_ClipXPopupModifier_Enum : public SvcEnumT<svc_ClipXPopupModifier> {};

// the ClipXMenuHandler class is used to manipulate menus

class ClipXMenuHandler : public Dispatchable {
protected:
  ClipXMenuHandler() {}
  virtual ~ClipXMenuHandler() {}

public:
  // valid flags:
  // MF_STRING (default)
  // MF_CHECKED
  // MF_GRAYED
  // MF_DISABLED
  // MF_ENABLED
  // MF_OWNERDRAW (you must implement onCustomSize/onCustomDraw)
  // MF_SEPARATOR (cmd and str are ignored)
  
  // add to the top
  void insertMenuItem(int flags, int cmd, const char *str) { _voidcall(CLIPX_MENUHANDLER_INSERTITEM, flags, cmd, str); }
  ClipXMenuHandler *insertPopupMenu(const char *str) { return _call(CLIPX_MENUHANDLER_INSERTMENU, (ClipXMenuHandler *)NULL, str); }

  // add to the bottom
  void addMenuItem(int flags, int cmd, const char *str) { _voidcall(CLIPX_MENUHANDLER_ADDITEM, flags, cmd, str); }
  ClipXMenuHandler *addPopupMenu(const char *str) { return _call(CLIPX_MENUHANDLER_ADDMENU, (ClipXMenuHandler *)NULL, str); }

  // modify menu
  void updateMenuItem(int newflag, int cmd, const char *new_str) { _voidcall(CLIPX_MENUHANDLER_UPDATEITEM, newflag, cmd, new_str); }
  void deleteMenuItem(int cmd) { _voidcall(CLIPX_MENUHANDLER_DELETEITEM, cmd); }
  void deletePopupMenu(ClipXMenuHandler *menu) { _voidcall(CLIPX_MENUHANDLER_DELETEMENU, menu); }

  enum {
    CLIPX_MENUHANDLER_INSERTITEM = 10,
    CLIPX_MENUHANDLER_INSERTMENU = 20,
    CLIPX_MENUHANDLER_ADDITEM    = 30,
    CLIPX_MENUHANDLER_ADDMENU    = 40,
    CLIPX_MENUHANDLER_UPDATEITEM = 50,
    CLIPX_MENUHANDLER_DELETEITEM = 60,
    CLIPX_MENUHANDLER_DELETEMENU = 70,
  };
};

// implement the ClipXPopupModifier service to monitor clipboards in real time

class ClipXPopupModifier : public ClipXPopupModifierI {
public:
  ClipXPopupModifier() {}
  virtual ~ClipXPopupModifier() {}

  virtual void customizeSystrayMenu(ClipXMenuHandler *menu) {}
  virtual void customizeHistoryMenu(ClipXMenuHandler *menu, int is_hotkey, int is_submenu) {}
  virtual void onCustomSize(int cmd, int *w, int *h) {}
  virtual void onCustomDraw(int cmd, HDC dc, RECT rcitem, int state) {}
  virtual int onCustomAccelerator(char c) { return -1; }
  virtual void onCommand(int cmd) {}
  virtual void onDeleteMenu(ClipXMenuHandler *menu) {}
};


#endif
