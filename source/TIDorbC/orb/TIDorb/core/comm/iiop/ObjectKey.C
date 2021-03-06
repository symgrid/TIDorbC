//////////////////////////////////////////////////////////////////////////////////
//
// File:        ObjectKey.C
// Description: 
//
// Rel:         01.00
// Created:     September, 2002
// Author:      Juan A. Caceres Exposito      ( caceres@tid.es   )
//
// Revised:
//
// (C) Copyright 2009 Telefonica Investigacion y Desarrollo
//     S.A.Unipersonal (Telefonica I+D)
//
// This file is part of Morfeo CORBA Platform.
//
// Morfeo CORBA Platform is free software: you can redistribute it and/or
// modify it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Morfeo CORBA Platform is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Morfeo CORBA Platform. If not, see
//
//   http://www.gnu.org/licenses
//
// Info about members and contributors of the MORFEO project
// is available at
//
//   http://morfeo-project.org
//
///////////////////////////////////////////////////////////////////////////////////

#include "TIDorb/core/comm/iiop/ObjectKey.h"

TIDorb::core::comm::iiop::ObjectKey::ObjectKey()
throw (TIDThr::SystemException) 
{
  _key = NULL;

  _marshaled_key= NULL;

  _url = NULL;
};

TIDorb::core::comm::iiop::ObjectKey::ObjectKey(TIDorb::core::cdr::CDRInputStream* key)
 throw (TIDThr::SystemException)
{
  _key = NULL;
  _marshaled_key = key;
  _url = NULL;
};
  
TIDorb::core::comm::iiop::ObjectKey::ObjectKey(TIDorb::core::poa::POAKey* key)
 throw (TIDThr::SystemException)
{
  _key = key;
  _marshaled_key = NULL;
  _url = NULL;
};

TIDorb::core::comm::iiop::ObjectKey::~ObjectKey()
 throw (TIDThr::SystemException) 
{
  delete _marshaled_key;
  delete _url;
};

	
bool TIDorb::core::comm::iiop::ObjectKey::operator==(const TIDorb::core::comm::iiop::ObjectKey& other) const
{   
  return getMarshaledKey()->get_buffer()->equal(*(other.getMarshaledKey()->get_buffer()));
};
	
void TIDorb::core::comm::iiop::ObjectKey::read(TIDorb::core::cdr::CDRInputStream& input)
{
  if (_marshaled_key != NULL)
    delete _marshaled_key; 

  _marshaled_key = input.read_encapsulation();

};
	
void 
TIDorb::core::comm::iiop::ObjectKey::write(TIDorb::core::cdr::CDROutputStream& output) const
{
  TIDorb::core::cdr::BufferCDR_ref buffer = getMarshaledKey()->get_buffer();
  output.write_buffer(*buffer);
};

const TIDorb::core::cdr::CDRInputStream* 
TIDorb::core::comm::iiop::ObjectKey::getMarshaledKey() const
{

  if(_marshaled_key == NULL) {

    TIDThr::Synchronized sync(*((ObjectKey*)this));

    if (_marshaled_key != NULL)
      return _marshaled_key;

    if(_key.is_null())
      throw CORBA::INTERNAL("Malformed Objectkey");
    
    TIDorb::core::cdr::CDROutputStream encapsulation (NULL);
    
    encapsulation.write_boolean(encapsulation.get_byte_order());
    
    _key->write(encapsulation);

    delete ((ObjectKey *) this)->_marshaled_key; 

    ((ObjectKey *) this)->_marshaled_key = 
      (TIDorb::core::cdr::CDRInputStream*) (encapsulation.create_input_stream());
  }
  
  return _marshaled_key;
};

TIDorb::core::poa::POAKey* TIDorb::core::comm::iiop::ObjectKey::get_key() const
{
  
  if(_key.is_null()) {
    
    TIDThr::Synchronized sync(*((ObjectKey*)this));

    if (!_key.is_null())
      return _key;

    getMarshaledKey();
    
    TIDorb::core::cdr::CDRInputStream encapsulation (*(_marshaled_key));
    
    ((ObjectKey*)this)->_key = new TIDorb::core::poa::POAKey();
    
    encapsulation.set_version(Version::VERSION_1_2);
    
    /* Already seetted when the encapsulation was readen	
       CORBA::Boolean byte_order;
       
       encapsulation.read_boolean(byte_order);
       
       encapsulation.set_byte_order(byte_order);
    */
    _key->read(encapsulation);
  }
  
  return _key;
};


char* TIDorb::core::comm::iiop::ObjectKey::get_url()
{
  if (_url != NULL)
    return strdup(_url);
  
  if(_marshaled_key != NULL) {
    
    _marshaled_key->rewind();
    
    // Recover length string
    CORBA::ULong url_len = _marshaled_key->buffer_available();

    // Read string
    _url = CORBA::string_alloc(url_len);
    _marshaled_key->read_octet_array((::CORBA::Octet*)_url, 0, url_len);
    _url[url_len] = '\0';

    return strdup(_url);
  }
  else 
    return 0;
}
