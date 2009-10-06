/////////////////////////////////////////////////////////////////////////
//
// File:        ThreadPolicyImpl.h
// Description:
//              
// Rel:         01.00
// Created:     November, 2002
//
// Revised:    
//
// Copyright 2002 Telefonica, I+D. Printed in Spain (Europe). All Rights
// Reserved.
// The copyright to the software program(s) is property of Telefonica I+D.
// The program(s) may be used and or copied only with the express written
// consent of Telefonica I+D or in acordance with the terms and conditions
// stipulated in the agreement/contract under which the program(s) have
// been supplied.
//
/////////////////////////////////////////////////////////////////////////

#include "TIDorb/core/poa/policies.h"

/**
 * Implementation of ThreadPolicy
 * @version 1.0
 */
 
#ifndef _TIDORB_CORE_POA_POLICIES_ThreadPolicyImpl_H_
#define _TIDORB_CORE_POA_POLICIES_ThreadPolicyImpl_H_

namespace TIDorb {
namespace core {
namespace poa {
namespace policies {
 
class ThreadPolicyImpl : public PortableServer::ThreadPolicy,
                         public CORBA::LocalObject
{
private:
  bool destroyed;
	PortableServer::ThreadPolicyValue _value;
  
public:
	ThreadPolicyImpl(PortableServer::ThreadPolicyValue value);
	
	~ThreadPolicyImpl();
    
  	PortableServer::ThreadPolicyValue value() throw();
  
  	CORBA::PolicyType policy_type() throw ();
  
	CORBA::Policy_ptr copy() throw();
  
  	bool _is_a(const char* repositoryIdentifier);
	
  	bool _is_equivalent(CORBA::Object_ptr other);
  	
  	void destroy() throw();
  	                                                    
};
}//policies
}//poa
}//core
}//TIDorb
#endif
