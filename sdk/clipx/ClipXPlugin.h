#ifndef GCLIPX_PLUGIN_H
#define GCLIPX_PLUGIN_H

// CLIPX PLUGIN SDK - DO NOT MODIFY

#include <wac/wac.h>
#include "ClipXHost.h"

extern ClipXHost *g_clipx;

#include <bfc/dispatch.h>

class svc_ClipXComponent : public Dispatchable {
protected:
  svc_ClipXComponent() {}
  virtual ~svc_ClipXComponent() {}

public:
  static GUID getServiceType() { GUID g = SVCTGUID_MK4CC('c','x','0','3'); return g; }
  static const char *getServiceName() { return "ClipX Component Service"; }

  WaComponent *getComponent() { return _call(SVC_CLIPX_COMPONENT_GETCOMPONENT, (WaComponent *)NULL); }
  void about(HWND parent) { _voidcall(SVC_CLIPX_COMPONENT_ABOUT, parent); }

  enum {
    SVC_CLIPX_COMPONENT_GETCOMPONENT = 10,
    SVC_CLIPX_COMPONENT_ABOUT        = 20,
  };
};

class ClipXComponentI : public svc_ClipXComponent {
protected:
  ClipXComponentI() {}
  virtual ~ClipXComponentI() {}

public:
  virtual WaComponent *getComponent()=0;
  virtual void _about() { about(NULL); }
  virtual void about(HWND parent)=0;

protected:
  RECVS_DISPATCH;
};

#include <api/service/servicei.h>
template <class T>
class ClipXComponentCreator : public waServiceFactoryTSingle<svc_ClipXComponent, T> {};

#include <api/service/svcenumt.h>

class svc_ClipXComponent_Enum : public SvcEnumT<svc_ClipXComponent> {};

class ClipXPlugin : public WAComponentClient, public ClipXComponentI {
public:
  virtual void onRegisterServices();
  virtual WaComponent *getComponent() { return this; }
  virtual void about(HWND parent)=0;
};

#define DECLARE_CLIPX_PLUGIN(PLUGIN_CLASS) \
_DECLARE_SERVICETSINGLE(svc_ClipXComponent, PLUGIN_CLASS); \
static PLUGIN_CLASS _plugin; \
WAComponentClient *the = &_plugin; \
PLUGIN_CLASS *plugin = &_plugin; 


#endif
