#ifndef CLIPX_CONFIGPAGE_H
#define CLIPX_CONFIGPAGE_H

// CLIPX PLUGIN SDK - DO NOT MODIFY

#include <bfc/dispatch.h>

class svc_ClipXConfigPage : public Dispatchable {
protected:
  svc_ClipXConfigPage() {}
  virtual ~svc_ClipXConfigPage() {}

public:
  static GUID getServiceType() { GUID g = SVCTGUID_MK4CC('c','x','0','2'); return g; }
  static const char *getServiceName() { return "ClipX Configuration Page Service"; }

  const char *getPageTitle() { return _call(SVC_CLIPX_CONFIGPAGE_GETPAGETITLE, (const char *)NULL); }
  HWND createPage(HWND parent) { return _call(SVC_CLIPX_CONFIGPAGE_CREATEPAGE, (HWND)NULL, parent); }
  void onDestroyPage(HWND dialog) { _voidcall(SVC_CLIPX_CONFIGPAGE_ONDESTROYPAGE, dialog); }
  void copySettings() { _voidcall(SVC_CLIPX_CONFIGPAGE_COPYSETTINGS); }
  void applySettings() { _voidcall(SVC_CLIPX_CONFIGPAGE_APPLYSETTINGS); }
  void saveSettings(const char *inifile, const char *section) { _voidcall(SVC_CLIPX_CONFIGPAGE_SAVESETTINGS, inifile, section); }
  void loadSettings(const char *inifile, const char *section) { _voidcall(SVC_CLIPX_CONFIGPAGE_LOADSETTINGS, inifile, section); }

  enum {
    SVC_CLIPX_CONFIGPAGE_GETPAGETITLE     = 10,
    SVC_CLIPX_CONFIGPAGE_CREATEPAGE       = 20,
    SVC_CLIPX_CONFIGPAGE_COPYSETTINGS     = 30,       
    SVC_CLIPX_CONFIGPAGE_APPLYSETTINGS    = 40,       
    SVC_CLIPX_CONFIGPAGE_SAVESETTINGS     = 50,
    SVC_CLIPX_CONFIGPAGE_LOADSETTINGS     = 60,
    SVC_CLIPX_CONFIGPAGE_ONDESTROYPAGE    = 70,
  };
};

class ClipXConfigPageI : public svc_ClipXConfigPage {
protected:
  ClipXConfigPageI() {}
  virtual ~ClipXConfigPageI() {}

public:
  virtual const char *getPageTitle()=0;
  virtual HWND createPage(HWND parent)=0;
  virtual void onDestroyPage(HWND dialog)=0;
  virtual void copySettings()=0;
  virtual void applySettings()=0;
  virtual void saveSettings(const char *inifile, const char *section)=0;
  virtual void loadSettings(const char *inifile, const char *section)=0;

protected:
  RECVS_DISPATCH;
};

#include <api/service/servicei.h>
template <class T>
class ClipXConfigPageCreator : public waServiceFactoryTSingle<svc_ClipXConfigPage, T> {};

#include <api/service/svcenumt.h>

class svc_ClipXConfigPage_Enum : public SvcEnumT<svc_ClipXConfigPage> {};

// implement the ClipXConfigPage service to monitor clipboards in real time

class ClipXConfigPage : public ClipXConfigPageI {
public:
  ClipXConfigPage() {}
  virtual ~ClipXConfigPage() {}

  virtual const char *getPageTitle() { return "Unnamed"; }
  virtual HWND createPage(HWND parent) { return NULL; }
  virtual void onDestroyPage(HWND dialog) {}
  virtual void copySettings() {}
  virtual void applySettings() {}
  virtual void saveSettings(const char *inifile, const char *section) {}
  virtual void loadSettings(const char *inifile, const char *section) {}
};

#endif
