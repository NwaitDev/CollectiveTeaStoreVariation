#include "ChipsFunctions.hpp"

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
void UserMachineInit(int& httpResponse_in, int& startTime_in, int& endTime_in, int& id_in, int& maxNbData_in, int& computerID_ctx, bool& active_inner, bool& waiting__inner, int& time_inner, bool& requiresAuth_inner, bool& newPage_inner, int&currentRequest_inner, int& httpRequest_inner, int& fromUserToInternet_out){

    // default values :
    maxNbData_in = 10;


    waiting__inner = false;
    time_inner = 0;
    computerID_ctx = id_in;

    //nb of data requested
    currentRequest_inner = (int) (randomdouble()*((double)maxNbData_in))+1; 

     // (auth ? -1 : 1)*((maxNbData+1)*ID + nbData) with nbData in [1, maxNbData]
    httpRequest_inner = (maxNbData_in+1)*computerID_ctx + currentRequest_inner;

    // httpResponse in the form of
    // response ? (authRequired ? -1 : 1)*(ID) : 0

    // outputs
    fromUserToInternet_out = httpRequest_inner;
}
void UserMachineThen(int& httpResponse_in, int& startTime_in, int& endTime_in, int& id_in, int& maxNbData_in, int& computerID_ctx, bool& active_inner, bool& waiting__inner, int& time_inner, bool& requiresAuth_inner, bool& newPage_inner, int&currentRequest_inner, int& httpRequest_inner, int& fromUserToInternet_out){
    newPage_inner = httpResponse_in !=0;
    requiresAuth_inner = httpResponse_in < 0;
    active_inner = (time_inner>=startTime_in) && (time_inner<endTime_in);
    if (!active_inner) {
        httpRequest_inner = 0;
    } else {
        if (!waiting__inner){
            currentRequest_inner = (int) (randomdouble()*(double)maxNbData_in)+1;
            httpRequest_inner = (maxNbData_in+1)*computerID_ctx + currentRequest_inner;
            if(requiresAuth_inner){
                httpRequest_inner = -httpRequest_inner;
            }
            waiting__inner = true;
        } else {
            if (newPage_inner){
                waiting__inner = false;
                if(requiresAuth_inner){
                    httpRequest_inner = -httpRequest_inner;
                }
            } else {
                waiting__inner = true;
                httpRequest_inner = 0;
            }
        }
    }
    time_inner = time_inner+1;

    // outputs
    fromUserToInternet_out = httpRequest_inner;
}

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
void ServerMachineInit(intarray& fromInternet_in, int& wpServed_in, int& maxNbData_in, int& httpResponse_inner, int& currentRequest_inner, bool& requestFound_inner, intarray& requestList_inner, int& fromServerToInternet_out, int& nbData_out, int& userID_out, bool& userAuth_out){
    // default values :
    maxNbData_in = 10;

    httpResponse_inner = 0;
    currentRequest_inner = 1;
    requestFound_inner = false;

    requestList_inner = zeros(100);

    // outputs
    fromServerToInternet_out = httpResponse_inner;
    nbData_out = requestList_inner[currentRequest_inner]%(maxNbData_in+1); 
    userID_out = requestList_inner[currentRequest_inner]/(maxNbData_in+1);
    userAuth_out = requestList_inner[currentRequest_inner]<0;
}

void ServerMachineThen(intarray& fromInternet_in, int& wpServed_in, int& maxNbData_in, int& httpResponse_inner, int& currentRequest_inner, bool& requestFound_inner, intarray& requestList_inner, int& fromServerToInternet_out, int& nbData_out, int& userID_out, bool& userAuth_out){

    ////////////////// treating client requests one by one
    requestList_inner[currentRequest_inner] = 0;

    for (auto i : range(100)) {
        if(fromInternet_in[i]!=0){
            requestList_inner[i] = fromInternet_in[i];
        }
    }

    for (auto reqShift : range(100)) { // weird way to do it to avoid starvation of clients
        if ( !requestFound_inner && (requestList_inner[(currentRequest_inner + reqShift)%100] != 0)) {
            requestFound_inner = true;
            currentRequest_inner = (currentRequest_inner + reqShift)%100;
        }
    }

    ////////////////// treating server responses one by one
    httpResponse_inner = wpServed_in;

    // outputs
    fromServerToInternet_out = httpResponse_inner;
    nbData_out = requestList_inner[currentRequest_inner]%(maxNbData_in+1); 
    userID_out = requestList_inner[currentRequest_inner]/(maxNbData_in+1);
    userAuth_out = requestList_inner[currentRequest_inner]<0;
}

// (input)
// int nbDataRcvd
// bool authDataRcvd
// int userIDRcvd

// (output)
// int nbData
// int reqID
// authProvided
void UserActionInterpreterInit(int& nbDataRcvd_in, bool& authDataRcvd_in, int& userIDRcvd_in, int& nbData_out, int& reqID_out, bool& authProvided_out){
    //outputs
    nbData_out = nbDataRcvd_in;
    reqID_out = userIDRcvd_in;
    authProvided_out = authDataRcvd_in;
}
void UserActionInterpreterThen(int& nbDataRcvd_in, bool& authDataRcvd_in, int& userIDRcvd_in, int& nbData_out, int& reqID_out, bool& authProvided_out){
    //outputs
    nbData_out = nbDataRcvd_in;
    reqID_out = userIDRcvd_in;
    authProvided_out = authDataRcvd_in;

}

// (input)
// bool authProvided

// (output)
// bool isAuthenticated
void AuthenticatorInit(bool& authProvided_in,bool& isAuthenticated_out){
    // outputs
    isAuthenticated_out = authProvided_in;
}
void AuthenticatorThen(bool& authProvided_in,bool& isAuthenticated_out){
    // outputs
    isAuthenticated_out = authProvided_in;
}

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
void RequestValidatorInit(int& nbData_in, int& requestID_in, bool& isAuthenticated_in, int& nbDataToFetch_inner, bool& needRedirection_inner, int& nbDataRequested_out, int& userID_out, bool& redirection_out){
    nbDataRequested_out = nbDataToFetch_inner;
    userID_out = requestID_in;
    redirection_out = needRedirection_inner;
}
void RequestValidatorThen(int& nbData_in, int& requestID_in, bool& isAuthenticated_in, int& nbDataToFetch_inner, bool& needRedirection_inner, int& nbDataRequested_out, int& userID_out, bool& redirection_out){

    needRedirection_inner = (nbData_in > 5) && (!isAuthenticated_in);
    if (!needRedirection_inner){
        nbDataToFetch_inner = nbData_in;
    } else {
        nbDataToFetch_inner = 0;
    }

    // outputs
    nbDataRequested_out = nbDataToFetch_inner;
    userID_out = requestID_in;
    redirection_out = needRedirection_inner;
}

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
void RequestLimiterInit(bool& redirection_in, int& maxRequests_in, int& userID_in, int& nbDataToFetch_in, int& nbAnsweredReqs_in, int& currentNbRequests_inner, bool& redirection_out, int& userID_out, int& dataQty_out){
    currentNbRequests_inner = 0;

    //outputs
    redirection_out = redirection_in;
    userID_out = userID_in;
    dataQty_out = nbDataToFetch_in;
}
void RequestLimiterThen(bool& redirection_in, int& maxRequests_in, int& userID_in, int& nbDataToFetch_in, int& nbAnsweredReqs_in, int& currentNbRequests_inner, bool& redirection_out, int& userID_out, int& dataQty_out){
    
    currentNbRequests_inner = currentNbRequests_inner - nbAnsweredReqs_in;
    if(!redirection_in){
        if ((currentNbRequests_inner + 1) <= maxRequests_in) {
            currentNbRequests_inner = currentNbRequests_inner + 1;
        } else {
            redirection_in = true;
            nbDataToFetch_in = 0;
        }
    }

    //outputs
    redirection_out = redirection_in;
    userID_out = userID_in;
    dataQty_out = nbDataToFetch_in;
}

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
void CacheInit(int& requestedData_in, int& cacheSize_in, int& maxCacheSize_inner, int& minCacheSize_inner, intarray& cache_inner, int& newestDataIndex_inner, bool& found_inner, int& foundIndex_inner, bool& foundInCache_out){
    maxCacheSize_inner = 100;
    minCacheSize_inner = 10;
    cache_inner = zeros(maxCacheSize_inner);
    newestDataIndex_inner = 0;
    found_inner = false;
    foundIndex_inner = 0;

    //outputs
    foundInCache_out = found_inner;
}
void CacheThen(int& requestedData_in, int& cacheSize_in, int& maxCacheSize_inner, int& minCacheSize_inner, intarray& cache_inner, int& newestDataIndex_inner, bool& found_inner, int& foundIndex_inner, bool& foundInCache_out){
    
    if(cacheSize_in > maxCacheSize_inner){
        cacheSize_in = maxCacheSize_inner;
    }
    if (cacheSize_in < minCacheSize_inner){
        cacheSize_in = minCacheSize_inner;
    }
    if(newestDataIndex_inner >= cacheSize_in){
        newestDataIndex_inner = 0;
    }

    if (!(requestedData_in > 0)){
        found_inner = false;
    } else {
        found_inner = false;
        for (auto i : range(cacheSize_in)) {
            if((!found_inner) && (cache_inner[i] == requestedData_in)){
                found_inner = true;
                foundIndex_inner = i;
            }
        }

        if (!found_inner) {
            newestDataIndex_inner = (newestDataIndex_inner + 1) % cacheSize_in;
            cache_inner [newestDataIndex_inner] = requestedData_in;
        } else {
            if(foundIndex_inner < newestDataIndex_inner){
                int temp;
                for (auto i : range(newestDataIndex_inner-foundIndex_inner)) {
                    temp = cache_inner[foundIndex_inner+i+1];
                    cache_inner[foundIndex_inner+i+1] = cache_inner[foundIndex_inner+i];
                    cache_inner[foundIndex_inner+i] = temp;
                }
            } else {
                int temp;
                for (auto i : range( cacheSize_in-foundIndex_inner + newestDataIndex_inner)) {
                    temp = cache_inner[(foundIndex_inner+i+1)%cacheSize_in];
                    cache_inner[(foundIndex_inner+i+1)%cacheSize_in] = cache_inner[(foundIndex_inner+i)%cacheSize_in];
                    cache_inner[(foundIndex_inner+i)%cacheSize_in] = temp;
                }
            }
        }
    }

    //outputs
    foundInCache_out = found_inner;
}

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
void DataProviderInit(bool& redirection_in, int& userID_in, int& dataQty_in, bool& cacheResponse_in, int& maxDifferentData_inner, int& maxUserID_inner, intarray& dataPerUserID_inner, int& currentlyTreatedUserRequest_inner, int& idToRespondTo_inner, int& dataToFetch_inner, double& time_inner, bool& cacheSearching_inner, bool& oneLessPendingRequest_inner, int& userID_out, int& cacheRequest_out, bool& oneLessPendingRequest_out, double& timeSpentOnReq_out, bool& enableTimeReading_out){
    maxDifferentData_inner = 40;
    maxUserID_inner = 100;
    dataPerUserID_inner = zeros(maxUserID_inner);
    currentlyTreatedUserRequest_inner = -1;

    ///////
    // Function output
    
    idToRespondTo_inner = 0;
    dataToFetch_inner = 0;

    time_inner = 0.;
    cacheSearching_inner = false;
    oneLessPendingRequest_inner = false;

    // outputs
    userID_out = idToRespondTo_inner; // already formatted as the http answer
    cacheRequest_out = dataToFetch_inner;
    oneLessPendingRequest_out = oneLessPendingRequest_inner;
    timeSpentOnReq_out = time_inner;
    enableTimeReading_out = oneLessPendingRequest_inner;
}
void DataProviderThen(bool& redirection_in, int& userID_in, int& dataQty_in, bool& cacheResponse_in, int& maxDifferentData_inner, int& maxUserID_inner, intarray& dataPerUserID_inner, int& currentlyTreatedUserRequest_inner, int& idToRespondTo_inner, int& dataToFetch_inner, double& time_inner, bool& cacheSearching_inner, bool& oneLessPendingRequest_inner, int& userID_out, int& cacheRequest_out, bool& oneLessPendingRequest_out, double& timeSpentOnReq_out, bool& enableTimeReading_out){
    oneLessPendingRequest_inner = false;
    idToRespondTo_inner = 0;
    if(userID_in != 0){
        if(redirection_in){
            idToRespondTo_inner = -userID_in;
        } else {
            dataPerUserID_inner[userID_in-1] = dataQty_in;
            if (currentlyTreatedUserRequest_inner < 0 ) {
                currentlyTreatedUserRequest_inner = userID_in-1;
            }
        }
    }

    // if we have pending requests and we are not occupied sending a response
    if (currentlyTreatedUserRequest_inner >=0 && idToRespondTo_inner==0) {

        if(cacheSearching_inner) {
            if(cacheResponse_in){
                // adding to current time a small increment
                // because searching the cache was fast
                time_inner = time_inner + 0.03;
            } else {
                // adding to current time a big increment
                // because requesting the database was long
                time_inner = time_inner + 2.0;
            }
            dataPerUserID_inner[currentlyTreatedUserRequest_inner] = dataPerUserID_inner[currentlyTreatedUserRequest_inner] -1;
        }

        if(dataPerUserID_inner[currentlyTreatedUserRequest_inner]>0){
            dataToFetch_inner = (int) (randomdouble()*((double)maxDifferentData_inner))+1;
            cacheSearching_inner = true;
        } else {
            //we finished treating the current request
            idToRespondTo_inner = currentlyTreatedUserRequest_inner +1;
            oneLessPendingRequest_inner = true;

            bool foundNewRequestPending = false;
            for (auto userReqShift : range(maxUserID_inner)) {
                if ((!foundNewRequestPending) && (dataPerUserID_inner[(currentlyTreatedUserRequest_inner + userReqShift)%maxUserID_inner] > 0)){
                    foundNewRequestPending = true;
                    currentlyTreatedUserRequest_inner = (currentlyTreatedUserRequest_inner + userReqShift)%maxUserID_inner;
                }
            }
            if (!foundNewRequestPending){
                cacheSearching_inner = false;
                currentlyTreatedUserRequest_inner = -1;
            } else {
                dataToFetch_inner = (int) (randomdouble()*((double)maxDifferentData_inner))+1;
                cacheSearching_inner = true;
            }
        }
    }

    // outputs
    userID_out = idToRespondTo_inner; // already formatted as the http answer
    cacheRequest_out = dataToFetch_inner;
    oneLessPendingRequest_out = oneLessPendingRequest_inner;
    timeSpentOnReq_out = time_inner;
    enableTimeReading_out = oneLessPendingRequest_inner;
}

// (default input accumulator) 
// c_intarray answers

// (target object)
// c_intarray

// (default channel output accumulator)
// c_intarray
void allDataProvidersOutputsCollect(c_intarray&, c_intarray&, c_intarray);
// (input)
// intarray respondToThisIDs

// (inner variables)
// int currentRequestAnswered
// intarray requestsToAnswerTo
// bool requestFound

// (output)
// int idToRespondTo
void WebPageServiceInit(intarray&,int&,intarray&,bool&,int);
void WebPageServiceThen(intarray&,int&,intarray&,bool&,int);
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
void PidControllerInit(double&, double&, bool&, double&, double&, double&, double&, double&, double&, double&, int&, int&, int&, int);
void PidControllerThen(double&, double&, bool&, double&, double&, double&, double&, double&, double&, double&, int&, int&, int&, int);
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