
/*  
 *  $Id$
 *
 *                              
 *                    L O S  A L A M O S
 *              Los Alamos National Laboratory
 *               Los Alamos, New Mexico 87545
 *                                  
 *  Copyright, 1986, The Regents of the University of California.
 *                                  
 *           
 *	Author Jeffrey O. Hill
 *	johill@lanl.gov
 *	505 665 1831
 */

#ifndef repeaterClienth
#define repeaterClienth

#ifdef epicsExportSharedSymbols
#define repeaterClienth_restore_epicsExportSharedSymbols
#undef epicsExportSharedSymbols
#endif

#include "shareLib.h"

#include "tsDLList.h"
#include "epicsSingleton.h"

#ifdef repeaterClienth_restore_epicsExportSharedSymbols
#define epicsExportSharedSymbols
#endif

#include "shareLib.h"

union osiSockAddr;

/*
 * one socket per client so we will get the ECONNREFUSED
 * error code (and then delete the client)
 */
class repeaterClient : public tsDLNode < repeaterClient > {
public:
    repeaterClient ( const osiSockAddr & from );
    bool connect ();
    bool sendConfirm ();
    bool sendMessage ( const void *pBuf, unsigned bufSize );
    void destroy ();
    bool verify ();
    bool identicalAddress ( const osiSockAddr &from );
    bool identicalPort ( const osiSockAddr &from );
    void * operator new ( size_t size );
    void operator delete ( void *pCadaver, size_t size );
protected:
    ~repeaterClient ();
private:
    osiSockAddr from;
    SOCKET sock;
    unsigned short port () const;
    static epicsSingleton < tsFreeList < class repeaterClient, 0x20 > > pFreeList;
};

#endif // repeaterClienth


