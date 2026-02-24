#ifndef __CHIPS_FCTS_HPP__
#define __CHIPS_FCTS_HPP__
#include "../Base/base.hpp"

void UserMachineInit(chips_int&, int&, int&, int&, int&, int&, bool&, bool&, int&, bool&, bool&, int&, int&, int&, int&);
void UserMachineThen(chips_int&, int&, int&, int&, int&, int&, bool&, bool&, int&, bool&, bool&, int&, int&, int&, int&);
void ServerMachineInit(intarray&, int&, int&, int&, int&, bool&, intarray&, int&, int&, bool&, int&, int&, int&, bool&);
void ServerMachineThen(intarray&, int&, int&, int&, int&, bool&, intarray&, int&, int&, bool&, int&, int&, int&, bool&);
void UserActionInterpreterInit(int&, bool&, int&, int&, int&, bool&);
void UserActionInterpreterThen(int&, bool&, int&, int&, int&, bool&);
void AuthenticatorInit(bool&,bool&);
void AuthenticatorThen(bool&,bool&);
void RequestValidatorInit(int&, int&, bool&, int&, bool&, int&, int&, bool&);
void RequestValidatorThen(int&, int&, bool&, int&, bool&, int&, int&, bool&);
void RequestLimiterInit(bool&, int&, int&, int&, int&, int&, bool&, chips_int&, int&);
void RequestLimiterThen(bool&, int&, int&, int&, int&, int&, bool&, chips_int&, int&);
void CacheInit(int&, int&, int&, int&, intarray&, int&, bool&, int&, bool&);
void CacheThen(int&, int&, int&, int&, intarray&, int&, bool&, int&, bool&);
void DataProviderInit(bool&, chips_int&, int&, bool&, int&, int&, intarray&, int&, int&, int&, double&, bool&, bool&, int&, int&, bool&, double&, bool&);
void DataProviderThen(bool&, chips_int&, int&, bool&, int&, int&, intarray&, int&, int&, int&, double&, bool&, bool&, int&, int&, bool&, double&, bool&);
void allDataProvidersOutputsCollect(int&, collective_intarray&, collective_intarray&, collective_intarray&, collective_intarray&, collective_intarray&, intarray&);
void WebPageServiceInit(intarray&,int&,intarray&,bool&,int&);
void WebPageServiceThen(intarray&,int&,intarray&,bool&,int&);
void responseToTheRightUserSpread(int&, collective_int&, collective_int&, collective_int&, chips_int&);
void aggregatingRequestsCollect(int&, collective_intarray&, collective_intarray&, collective_intarray&, collective_intarray&, collective_intarray&, intarray&);
void PidControllerInit(double&,double&,bool&,double&,double&,double&,double&,double&,double&,double&,int&,int&,int&,int&);
void PidControllerThen(double&,double&,bool&,double&,double&,double&,double&,double&,double&,double&,int&,int&,int&,int&);
void numberOfRespondedRequestsCollect(bool&, collective_int&, collective_int&, collective_int&, collective_int&, collective_int&, int&);
void broadcastRedirectionSpread(collective_bool&, collective_bool&, collective_bool&, bool&);
void broadcastDataQtySpread(collective_int&, collective_int&, collective_int&, int&);
void findRightDataProviderSpread(collective_int&, collective_int&, collective_int&, collective_int&, collective_int&,collective_int&, chips_int&);

#endif // __CHIPS_FCTS_HPP__