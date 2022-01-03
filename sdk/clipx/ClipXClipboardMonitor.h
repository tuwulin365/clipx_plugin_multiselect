#ifndef CLIPX_CLIPBOARDMONITOR_H
#define CLIPX_CLIPBOARDMONITOR_H

// CLIPX PLUGIN SDK - DO NOT MODIFY

#include <bfc/dispatch.h>
#include <shellapi.h>

class svc_ClipXClipboardMonitor : public Dispatchable {
protected:
  svc_ClipXClipboardMonitor() {}
  virtual ~svc_ClipXClipboardMonitor() {}

public:
  static GUID getServiceType() { GUID g = SVCTGUID_MK4CC('c','x','0','1'); return g; }
  static const char *getServiceName() { return "ClipX Clipboard Monitoring Service"; }

  int onNewTextClipboard(const char *text) { return _call(SVC_CLIPX_CLIPBOARDMONITOR_ONNEWTEXTCLIPBOARD, 1, text); }
  int onNewBitmapClipboard(HBITMAP bmp) { return _call(SVC_CLIPX_CLIPBOARDMONITOR_ONNEWBITMAPCLIPBOARD, 1, bmp); }
  int onNewDIBitmapClipboard(BITMAPINFO *dib) { return _call(SVC_CLIPX_CLIPBOARDMONITOR_ONNEWDIBITMAPCLIPBOARD, 1, dib); }
  int onNewFileListClipboard(HDROP filelist) { return _call(SVC_CLIPX_CLIPBOARDMONITOR_ONNEWFILELISTCLIPBOARD, 1, filelist); }

  enum {
    SVC_CLIPX_CLIPBOARDMONITOR_ONNEWTEXTCLIPBOARD     = 10,
    SVC_CLIPX_CLIPBOARDMONITOR_ONNEWBITMAPCLIPBOARD   = 20,
    SVC_CLIPX_CLIPBOARDMONITOR_ONNEWDIBITMAPCLIPBOARD = 30,
    SVC_CLIPX_CLIPBOARDMONITOR_ONNEWFILELISTCLIPBOARD = 40,
  };
};

class ClipXClipboardMonitorI : public svc_ClipXClipboardMonitor {
protected:
  ClipXClipboardMonitorI() {}
  virtual ~ClipXClipboardMonitorI() {}

public:
  virtual int onNewTextClipboard(const char *text)=0;
  virtual int onNewBitmapClipboard(HBITMAP bmp)=0;
  virtual int onNewDIBitmapClipboard(BITMAPINFO *dib)=0;
  virtual int onNewFileListClipboard(HDROP filelist)=0;

protected:
  RECVS_DISPATCH;
};

#include <api/service/servicei.h>
template <class T>
class ClipXClipboardMonitorCreator : public waServiceFactoryTSingle<svc_ClipXClipboardMonitor, T> {};

#include <api/service/svcenumt.h>

class svc_ClipXClipboardMonitor_Enum : public SvcEnumT<svc_ClipXClipboardMonitor> {};

// implement the ClipXClipboardMonitor service to monitor clipboards in real time

class ClipXClipboardMonitor : public ClipXClipboardMonitorI {
public:
  ClipXClipboardMonitor() {}
  virtual ~ClipXClipboardMonitor() {}

  virtual int onNewTextClipboard(const char *text) { return 1; }
  virtual int onNewBitmapClipboard(HBITMAP bmp) { return 1; }
  virtual int onNewDIBitmapClipboard(BITMAPINFO *dib) { return 1; }
  virtual int onNewFileListClipboard(HDROP filelist) { return 1; }
};

#endif
