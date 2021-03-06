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

#if !defined(__WRAPPERCLASSHANDLER_OF_AXIS_INCLUDED__)
#define __WRAPPERCLASSHANDLER_OF_AXIS_INCLUDED__

#include <axis/BasicHandler.hpp>

/**
 * @class WrapperClassHandler
 * @brief
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

AXIS_CPP_NAMESPACE_START

class WrapperClassHandler : public HandlerBase 
{
public:
    WrapperClassHandler(){};
    virtual ~WrapperClassHandler(){};
    virtual AXIS_BINDING_STYLE AXISCALL getBindingStyle()=0;
    int AXISCALL getType(){return WEBSERVICE_HANDLER;};
    virtual int AXISCALL init() { return AXIS_SUCCESS; }; // We do not need init and fini for the service wrapper
    virtual int AXISCALL fini() { return AXIS_SUCCESS; };
};

AXIS_CPP_NAMESPACE_END

#endif 

