#ifndef __CHIPS_FCTS_HPP__
#define __CHIPS_FCTS_HPP__
#include "../Base/base.hpp"

void UserMachineInit(int&, int&, int&, int&, int&, int&, bool&, bool&, int&, bool&, bool&, int&, int&, int&);
void UserMachineThen(int&, int&, int&, int&, int&, int&, bool&, bool&, int&, bool&, bool&, int&, int&, int&);
void ServerMachineInit(IntArray&, int&, int&, int&, int&, bool&, IntArray&, int&, int&, int&, bool&);
void ServerMachineThen(IntArray&, int&, int&, int&, int&, bool&, IntArray&, int&, int&, int&, bool&);
void UserActionInterpreterInit(int&, bool&, int&, int&, int&, bool&);
void UserActionInterpreterThen(int&, bool&, int&, int&, int&, bool&);
void AuthenticatorInit(bool&,bool&);
void AuthenticatorThen(bool&,bool&);
void RequestValidatorInit(int&, int&, bool&, int&, bool&, int&, int&, bool&);
void RequestValidatorThen(int&, int&, bool&, int&, bool&, int&, int&, bool&);
void RequestLimiterInit(bool&, int&, int&, int&, int&, int&, bool&, int&, int&);
void RequestLimiterThen(bool&, int&, int&, int&, int&, int&, bool&, int&, int&);
void CacheInit(int&, int&, int&, int&, IntArray&, int&, bool&, int&, bool&);
void CacheThen(int&, int&, int&, int&, IntArray&, int&, bool&, int&, bool&);
void DataProviderInit(bool&, int&, int&, bool&, int&, int&, IntArray&, int&, int&, int&, double&, bool&, bool&, int&, int&, bool&, double&, bool&);
void DataProviderThen(bool&, int&, int&, bool&, int&, int&, IntArray&, int&, int&, int&, double&, bool&, bool&, int&, int&, bool&, double&, bool&);
void allDataProvidersOutputsCollect(int&, c_IntArray&, c_IntArray&, c_IntArray&, c_IntArray&, c_IntArray&, IntArray&);
void WebPageServiceInit(IntArray&,int&,IntArray&,bool&,int&);
void WebPageServiceThen(IntArray&,int&,IntArray&,bool&,int&);
void responseToTheRightUserSpread(int&, c_int&, c_int&, c_int&, int&);
void aggregatingRequestsCollect(int&, c_IntArray&, c_IntArray&, c_IntArray&, c_IntArray&, c_IntArray&, IntArray&);
void PidControllerInit(double&,double&,bool&,double&,double&,double&,double&,double&,double&,double&,int&,int&,int&,int&);
void PidControllerThen(double&,double&,bool&,double&,double&,double&,double&,double&,double&,double&,int&,int&,int&,int&);
void numberOfRespondedRequestsCollect(bool&, c_int&, c_int&, c_int&, c_int&, c_int&, int&);
void broadcastRedirectionSpread(c_bool&, c_bool&, c_bool&, bool&);
void broadcastDataQtySpread(c_int&, c_int&, c_int&, int&);
void findRightDataProviderSpread(c_int&, c_int&, c_int&, c_int&, c_int&,c_int&, int&);

#endif // __CHIPS_FCTS_HPP__