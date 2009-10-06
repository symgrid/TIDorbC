///////////////////////////////////////////////////////////////////////////
//
// File:        TIDSocket_ConnectionPendingException.h
// Description: This file contains the ConnectionPending Exception class methods
// Rel:         01.00
// Created:     May, 2001
// Author:      Pablo Rodriguez Archilla      ( pra@tid.es   )
//
// Revised:
//
// Copyright 2001 Telefonica, I+D. Printed in Spain (Europe). All Rights
// Reserved.
// The copyright to the software program(s) is property of Telefonica I+D.
// The program(s) may be used and or copied only with the express written
// consent of Telefonica I+D or in acordance with the terms and conditions
// stipulated in the agreement/contract under which the program(s) have
// been supplied.
//
///////////////////////////////////////////////////////////////////////////

#include "TIDSocket.h"


#ifndef __TID_SOCKET_CONNECTION_PENDING_EXCEPTION_H__
#define __TID_SOCKET_CONNECTION_PENDING_EXCEPTION_H__


namespace TIDSocket
{


class ConnectionPendingException : public Exception
{
    public:
        ConnectionPendingException(const char* msg = "", int errnum = 0)
            throw() : Exception(msg, errnum) {}

        virtual ~ConnectionPendingException()
            throw() {}

        const char* getName() const
            throw() { return "TIDSocket::ConnectionPendingException"; }
};


} //namespace TIDSocket


#endif //__TID_SOCKET_CONNECTION_PENDING_EXCEPTION_H__
