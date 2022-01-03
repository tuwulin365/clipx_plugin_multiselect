#include <precomp.h>
#include "ClipXPlugin.h"
#include "ClipXHost.h"

// CLIPX PLUGIN SDK - DO NOT MODIFY

#define CBCLASS ClipXComponentI
START_DISPATCH;
  CB(SVC_CLIPX_COMPONENT_GETCOMPONENT, getComponent);
  case SVC_CLIPX_COMPONENT_ABOUT:
    if (nparam == 0) vcb(&CBCLASS::_about, retval, params);
    else vcb(&CBCLASS::about, retval, params);
    break;
END_DISPATCH;
#undef CBCLASS

ClipXHost *g_clipx = NULL;

void ClipXPlugin::onRegisterServices() {
  waServiceFactory *factory = WASABI_API_SVC->service_getServiceByGuid(CLIPX_HOST_GUID);
  ASSERT(factory);
  g_clipx = reinterpret_cast<ClipXHost *>(factory->getInterface());
  ASSERT(g_clipx);
  WAComponentClient::onRegisterServices();
}
