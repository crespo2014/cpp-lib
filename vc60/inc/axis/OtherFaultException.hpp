/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
 
#ifndef __OTHERFAULTEXCEPTION_H_OF_AXIS_INCLUDED_
#define __OTHERFAULTEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <axis/SoapFaultException.hpp>

/**
 * @file OtherFaultException.hpp
 */

AXIS_CPP_NAMESPACE_START

/**
 * @class OtherFaultException
 * @brief A server-generated soap fault exception
 * 
 * An exception thrown back to a client application that represents a soap
 * fault generated by the server.
 * 
 * @author Mark Whitlock
 */

class STORAGE_CLASS_INFO OtherFaultException : public SoapFaultException
{
public:
    /**
     * Default constructor
     */
	OtherFaultException();

    /**
     * Constructor
     * 
     * @param code is the SOAP faultcode
     * @param string is the SOAP faultstring
     * @param actor is the SOAP faultactor
     * @param detail is the SOAP fault detail
     * @param exceptionCode is the axis exception code
     */
	OtherFaultException(const AxisChar *code, const AxisChar *string, 
		const AxisChar *actor, const AxisChar *detail, int exceptionCode);

    /**
     * Copy constructor
     * 
     * @param ae is the AxisException to be copied
     */
	OtherFaultException(AxisException& ae);

    /**
     * Copy constructor
     * 
     * @param copy is the OtherFaultException to be copied
     */
	OtherFaultException(const OtherFaultException& copy);
    
    /**
     * Assignment operator
     * 
     * @param other is the OtherFaultException to be copied
     * @return reference to this
     */
	virtual OtherFaultException& operator=(OtherFaultException other);

    /**
     * Destructor
     */
	virtual ~OtherFaultException() throw();

    /**
     * Returns the SOAP fault detail
     * 
     * @return fault detail
     */
	virtual const AxisChar *getFaultDetail() const;

    /**
     * Set SOAP fault detail
     * 
     * @param detail is the SOAP fault detail
     */
	virtual void setFaultDetail(const AxisChar *detail);
private:
    /**
     * SOAP fault detail
     */
	AxisChar *m_detail;
};

AXIS_CPP_NAMESPACE_END

#endif

