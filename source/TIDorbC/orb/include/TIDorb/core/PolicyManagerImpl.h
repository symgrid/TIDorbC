//////////////////////////////////////////////////////////////////////////////////
//
// File:        PolicyManagerImpl.h
// Description: PolicyManager implementation.
//
// Rel:         01.00
// Created:     September, 2002
// Author:      Juan A. Caceres Exposito      ( caceres@tid.es   )
//
// Revised:
//
// Copyright 2002 Telefonica, I+D. Printed in Spain (Europe). All Rights Reserved.
// The copyright to the software program(s) is property of Telefonica I+D.
// The program(s) may be used and or copied only with the express written
// consent of Telefonica I+D or in acordance with the terms and conditions
// stipulated in the agreement/contract under which the program(s) have
// been supplied.
//
///////////////////////////////////////////////////////////////////////////////////

#include "TIDorb/core.h"

#ifndef __TIDorb_core_PolicyManagerImpl_H_
#define __TIDorb_core_PolicyManagerImpl_H_

#include "CORBA.h"


namespace TIDorb {
namespace core {

class PolicyManagerImpl : public virtual CORBA::PolicyManager,
                          public virtual CORBA::LocalObject
{
  protected:
    TIDorb::core::TIDORB* _orb;

  public:
    PolicyManagerImpl(TIDorb::core::TIDORB* orb);

    TIDorb::core::PolicyContext& getPolicyContext();

    CORBA::PolicyList* get_policy_overrides(const CORBA::PolicyTypeSeq& ts);

    void set_policy_overrides(const CORBA::PolicyList& policies,
                              CORBA::SetOverrideType set_add)
      throw (CORBA::InvalidPolicies);
};

}
}

#endif

