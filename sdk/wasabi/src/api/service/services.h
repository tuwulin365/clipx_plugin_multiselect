#ifndef _SERVICES_H
#define _SERVICES_H

#include <bfc/std_mkncc.h> // for MKnCC()

// lower-case service names are reserved by Nullsoft for future use
// upper-case service names are for 3rd parties to extend the service system

// if you have a service that is unique to a component, make it type
// UNIQUE and register it by GUID

namespace WaSvc {
  enum {
    NONE=MK4CC('n','o','n','e'),
    UNIQUE=MK4CC('u','n','i','q'),                  // for unique services, enumed by GUID
    CONTEXTCMD=MK4CC('c','c','m','d'),              // context menu command	svc_contextCmd.h
    DEVICE=MK3CC('d','e','v'),                   // portable device	svc_device.h
    FILEREADER=MK4CC('f','s','r','d'),	            // file system reader (disk, zip, http)
    FILESELECTOR=MK4CC('f','s','e','l'),            // file selector	svc_filesel.h
    STORAGEVOLENUM=MK4CC('f','s','e','n'),          // storage volume enumerator.
    IMAGEGENERATOR=MK4CC('i','m','g','n'),          // image generator	svc_imggen.h
    IMAGELOADER=MK4CC('i','m','g','l'),	            // image loader		svc_imgload.h
    IMAGEWRITER=MK4CC('i','m','g','w'),		// image writer
    ITEMMANAGER=MK4CC('i','m','g','r'),	            // item manager		svc_itemmgr.h
    PLAYLISTREADER=MK4CC('p','l','r','d'),          // playlist reader
    PLAYLISTWRITER=MK4CC('p','l','w','r'),          // playlist writer
    MEDIACONVERTER=MK4CC('c','o','n','v'),          // media converter
    MEDIACORE=MK4CC('c','o','r','e'),               // media core
    MEDIARECORDER=MK4CC('m','r','e','c'),           // media recorder
    SCRIPTOBJECT=MK4CC('m','a','k','i'),            // third party script object
//    TRANSLATOR=MK4CC('x','l','a','t'),            // text translator
    WINDOWCREATE=MK4CC('w','n','d','c'),            // window creator
    XMLPROVIDER=MK4CC('x','m','l','p'),	            // xml provider
    DB=MK2CC('d','b'),                        // database
    SKINFILTER=MK4CC('f','l','t','r'),              // bitmap/colorref skin filter
    METADATA=MK4CC('m','t','d','t'),                // play item meta data
    METATAG=MK4CC('m','t','t','g'),                 // metadata tagging of play items
    EVALUATOR=MK4CC('e','v','a','l'),               // evaluate a string
    MINIBROWSER=MK2CC('m','b'),               // minibrowser
    TOOLTIPSRENDERER=MK4CC('t','t','i','p'),        // tooltips renderer
    XUIOBJECT=MK4CC('x','u','i','o'),               // xml gui objects
    STRINGCONVERTER=MK4CC('u','t','f','8'),         // unicode string conversion
    ACTION=MK3CC('a','c','t'),                   // custom actions (ie: for buttons)
    COREADMIN=MK4CC('c','a','d','m'),               // core administrator
    DROPTARGET=MK4CC('d','r','o','p'),	            // drop targets
    OBJECTDIR=MK4CC('o','b','j','d'),               // object directory
    TEXTFEED=MK4CC('t','x','t','f'),                // text feed, to send text to various XUI objects (ie: <Text> by using display="textfeedid"
    ACCESSIBILITY=MK4CC('a','c','c','s'),           // accessibility service
    ACCESSIBILITYROLESERVER=MK4CC('r','o','l','e'), // accessibility roleServer services
    EXPORTER=MK3CC('e','x','p'),                 // exporter
    COLLECTION=MK4CC('c','l','c','t'),              // named xml overridable collection
    REDIRECT=MK4CC('r','e','d','r'),                // filename redirect
    FONTRENDER=MK4CC('f','o','n','t'),              // font renderer (bitmap/truetype/freetype)
    SRCCLASSFACTORY=MK4CC('c','l','f','a'),         // source code class factory
    SRCEDITOR=MK4CC('s','e','d','t'),               // source code editor
  };
};

#endif
