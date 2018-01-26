/**
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2009-2016 ObdDiag.Net. All rights reserved.
 *
 */

#ifndef __OBD_PROFILE_H__ 
#define __OBD_PROFILE_H__

#include <obd_protocol_inc/padapter.h>

class ISO15031_5 {
private:
    ISO15031_5();
public:
    static ISO15031_5* instance();
    void getProfileDescription() const;
    void getProtocolDescription() const;
    void getProtocolDescriptionNum() const;
    int setProtocol(int protocol, bool refreshConnection);
    void sendHeartBeat();
    void dumpBuffer();
    void closeProtocol();
    void onRequest(const util::string& cmdString);
    int getProtocol() const;
    void wiringCheck();
    int kwDisplay();
private:
    bool sendLengthCheck(const uint8_t* msg, int len);
    int onRequestImpl(const util::string& cmdString);
    ProtocolAdapter* adapter_;
};

#endif //__OBD_PROFILE_H__
