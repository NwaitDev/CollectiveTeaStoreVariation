#include "../Base/base.hpp"


// (input) 
// int httpResponse
// int startTime
// int endTime
// int id
// int maxNbData

// (ctx) 
// int computerID

// (inner variables)
// bool active
// bool waiting
// int time
// bool requiresAuth
// bool newPage
// int currentRequest
// int httpRequest

// (output)
// int fromUserToInternet
void UserMachineInit(int&, int&, int&, int&, int&, int&, bool&, bool&, int&, bool&, bool&, int&, int&, int&);
void UserMachineThen(int&, int&, int&, int&, int&, int&, bool&, bool&, int&, bool&, bool&, int&, int&, int&);
// (input)
// intarray fromInternet
// int wpServed
// int maxNbData

// (inner variables)
// int httpResponse
// int currentRequest
// bool requestFound
// intarray requestList

// (output)
// int fromServerToInternet
// int nbData
// int userID
// bool userAuth
void ServerMachineInit(intarray&, int&, int&, int&, int&, bool&, intarray&, int&, int&, int&, bool&);
void ServerMachineThen(intarray&, int&, int&, int&, int&, bool&, intarray&, int&, int&, int&, bool&);
// (input)
// int nbDataRcvd
// bool authDataRcvd
// int userIDRcvd

// (output)
// int nbData
// int reqID
// authProvided
void UserActionInterpreterInit(int&, bool&, int&, int&, int&, bool&);
void UserActionInterpreterThen(int&, bool&, int&, int&, int&, bool&);
// (input)
// bool authProvided

// (output)
// bool isAuthenticated
void AuthenticatorInit(bool&,bool&);
void AuthenticatorThen(bool&,bool&);
// (output)
// int nbData
// int requestID
// bool isAuthenticated

// (inner variables)
// int nbDataToFetch
// bool needRedirection

// (output)
// int nbDataRequested
// int userID
// bool redirection
void RequestValidatorInit(int&, int&, bool&, int&, bool&, int&, int&, bool&);
void RequestValidatorThen(int&, int&, bool&, int&, bool&, int&, int&, bool&);
// (input)
// bool redirection
// int maxRequests
// int userID
// int nbDataToFetch
// int nbAnsweredReqs

// (inner variables)
// int currentNbRequests

// (output)
// bool redirection
// int userID
// int dataQty
void RequestLimiterInit(bool&, int&, int&, int&, int&, int&, bool&, int&, int&);
void RequestLimiterThen(bool&, int&, int&, int&, int&, int&, bool&, int&, int&);
// (input)
// int requestedData
// int cacheSize

// (inner variables)
// int maxCacheSize
// int minCacheSize
// intarray cache
// int newestDataIndex
// bool found
// int foundIndex

// (output)
// bool foundInCache
void CacheInit(int&, int&, int&, int&, intarray&, int&, bool&, int&, bool&);
void CacheThen(int&, int&, int&, int&, intarray&, int&, bool&, int&, bool&);
// (input)
// bool redirection
// int userID
// int dataQty
// bool cacheResponse

// (inner variables)
// int maxDifferentData
// int maxUserID
// intarray dataPerUserID
// int currentlyTreatedUserRequest
// int idToRespondTo
// int dataToFetch
// float time
// bool cacheSearching
// bool oneLessPendingRequest

// (output)
// int userID
// cacheRequest
// oneLessPendingRequest
// timeSpentOnReq
// enableTimeReading
void DataProviderInit(bool&, int&, int&, bool&, int&, int&, intarray&, int&, int&, int&, double&, bool&, bool&, int&, int&, bool&, double&, bool&);
void DataProviderThen(bool&, int&, int&, bool&, int&, int&, intarray&, int&, int&, int&, double&, bool&, bool&, int&, int&, bool&, double&, bool&);
// (default input accumulator) 
// c_intarray answers

// (target object)
// c_intarray

// (default channel output accumulator)
// c_intarray
void allDataProvidersOutputsCollect(c_intarray&, c_intarray&, c_intarray&);
// (input)
// intarray respondToThisIDs

// (inner variables)
// int currentRequestAnswered
// intarray requestsToAnswerTo
// bool requestFound

// (output)
// int idToRespondTo
void WebPageServiceInit(intarray&,int&,intarray&,bool&,int&);
void WebPageServiceThen(intarray&,int&,intarray&,bool&,int&);
// (default input accumulator) 
// c_int fromInternet

// (target object)
// c_int

// (default channel output accumulator)
// c_int
void responseToTheRightUserSpread(c_int&, c_int&, c_int&);
// (default input accumulator) 
// c_intarray currentListOfRequests

// (target object)
// c_intarray

// (default channel output accumulator)
// c_intarray
void aggregatingRequestsCollect(c_intarray&, c_intarray&, c_intarray&);
// (input)
// float requested_time
// float resulting_time
// bool enabled

// (inner variables)
// float derivative
// float integral
// float error
// float dt
// float p
// float i
// float d
// int knob_value
// int min_knob_value
// int max_knob_value

// (output)
// int knob
void PidControllerInit(double&, double&, bool&, double&, double&, double&, double&, double&, double&, double&, int&, int&, int&, int&);
void PidControllerThen(double&, double&, bool&, double&, double&, double&, double&, double&, double&, double&, int&, int&, int&, int&);
// (default input accumulator)
// c_bool redirection

// (target object)
// c_bool

// (default channel output accumulator)
// c_bool
void broadcastRedirectionSpread(c_bool&, c_bool&, c_bool&);
// (default input accumulator)
// c_int dataQtyToFind

// (target object)
// c_int

// (default channel output accumulator)
// c_int
void broadcastDataQtySpread(c_int&, c_int&, c_int&);
// (default input accumulator)
// c_int userID
// c_int nbJumps

// (target object)
// c_int

// (next object accumulator)
// c_int&, c_int

// (prev object accumulator)
// stop
void findRightDataProviderSpread(c_int&, c_int&, c_int&, c_int&, c_int&);