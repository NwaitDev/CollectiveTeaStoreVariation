#include "ChipsFunctions.hpp"
#include <algorithm>


void UserMachineInit(int& httpResponse_in, int& startTime_in, int& endTime_in, int& id_in, int& maxNbData_in, int& computerID_ctx, bool& active_inner, bool& waiting__inner, int& time_inner, bool& requiresAuth_inner, bool& newPage_inner, int&currentRequest_inner, int& httpRequest_inner, int& fromUserToInternet_out){

    // default values :
    maxNbData_in = 10;


    waiting__inner = false;
    time_inner = 0;
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
    computerID_ctx = id_in;
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

void ServerMachineInit(IntArray& fromInternet_in, int& wpServed_in, int& maxNbData_in, int& httpResponse_inner, int& currentRequest_inner, bool& requestFound_inner, IntArray& requestList_inner, int& fromServerToInternet_out, int& nbData_out, int& userID_out, bool& userAuth_out){
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

void ServerMachineThen(IntArray& fromInternet_in, int& wpServed_in, int& maxNbData_in, int& httpResponse_inner, int& currentRequest_inner, bool& requestFound_inner, IntArray& requestList_inner, int& fromServerToInternet_out, int& nbData_out, int& userID_out, bool& userAuth_out){

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

void AuthenticatorInit(bool& authProvided_in,bool& isAuthenticated_out){
    // outputs
    isAuthenticated_out = authProvided_in;
}
void AuthenticatorThen(bool& authProvided_in,bool& isAuthenticated_out){
    // outputs
    isAuthenticated_out = authProvided_in;
}

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


void CacheInit(int& requestedData_in, int& cacheSize_in, int& maxCacheSize_inner, int& minCacheSize_inner, IntArray& cache_inner, int& newestDataIndex_inner, bool& found_inner, int& foundIndex_inner, bool& foundInCache_out){
    maxCacheSize_inner = 100;
    minCacheSize_inner = 10;
    cache_inner = zeros(maxCacheSize_inner);
    newestDataIndex_inner = 0;
    found_inner = false;
    foundIndex_inner = 0;

    //outputs
    foundInCache_out = found_inner;
}
void CacheThen(int& requestedData_in, int& cacheSize_in, int& maxCacheSize_inner, int& minCacheSize_inner, IntArray& cache_inner, int& newestDataIndex_inner, bool& found_inner, int& foundIndex_inner, bool& foundInCache_out){
    
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

void DataProviderInit(bool& redirection_in, int& userID_in, int& dataQty_in, bool& cacheResponse_in, int& maxDifferentData_inner, int& maxUserID_inner, IntArray& dataPerUserID_inner, int& currentlyTreatedUserRequest_inner, int& idToRespondTo_inner, int& dataToFetch_inner, double& time_inner, bool& cacheSearching_inner, bool& oneLessPendingRequest_inner, int& userID_out, int& cacheRequest_out, bool& oneLessPendingRequest_out, double& timeSpentOnReq_out, bool& enableTimeReading_out){
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
void DataProviderThen(bool& redirection_in, int& userID_in, int& dataQty_in, bool& cacheResponse_in, int& maxDifferentData_inner, int& maxUserID_inner, IntArray& dataPerUserID_inner, int& currentlyTreatedUserRequest_inner, int& idToRespondTo_inner, int& dataToFetch_inner, double& time_inner, bool& cacheSearching_inner, bool& oneLessPendingRequest_inner, int& userID_out, int& cacheRequest_out, bool& oneLessPendingRequest_out, double& timeSpentOnReq_out, bool& enableTimeReading_out){
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


void allDataProvidersOutputsCollect(int input, c_IntArray& answers, c_IntArray& prev_input_answers, c_IntArray& next_input_answers, c_IntArray& prev_output_answers, c_IntArray& next_output_answers, IntArray& output){
    if(input!=0){
        if(input>0){
            std::get<0>(answers)[input-1] = input;
        } else {
            std::get<0>(answers)[-input-1] = input;
        }
    }
    for (auto i : range(100)) {
        if(std::get<0>(prev_input_answers)[i]!=0){
            std::get<0>(answers)[i] = std::get<0>(prev_input_answers)[i];
        }
        if(std::get<0>(next_input_answers)[i]!=0){
            std::get<0>(answers)[i] = std::get<0>(next_input_answers)[i];
        }
    }

    next_output_answers = cpy(answers);
    prev_output_answers = cpy(answers);
    output = std::get<0>(answers);
}


void WebPageServiceInit(IntArray& respondToThisIDs_in, int& currentRequestAnswered_inner, IntArray& requestsToAnswerTo_inner, bool& requestFound_inner, int& idToRespondTo_out){

    currentRequestAnswered_inner = 0;
    requestsToAnswerTo_inner = zeros(100);
    requestFound_inner = false;

    //outputs
    idToRespondTo_out = requestsToAnswerTo_inner[currentRequestAnswered_inner];
}
void WebPageServiceThen(IntArray& respondToThisIDs_in, int& currentRequestAnswered_inner, IntArray& requestsToAnswerTo_inner, bool& requestFound_inner, int& idToRespondTo_out){

    requestsToAnswerTo_inner[currentRequestAnswered_inner] = 0;
    requestFound_inner = false;
    for (auto i : range(100)) {
        if(respondToThisIDs_in[i]!=0){
            requestsToAnswerTo_inner[i] = respondToThisIDs_in[i];
        }
    }

    for (auto reqShift : range(100)) { // weird way to do it to avoid starvation of clients
        if ( !requestFound_inner && (requestsToAnswerTo_inner[(currentRequestAnswered_inner + reqShift)%100] != 0)) {
            currentRequestAnswered_inner = (currentRequestAnswered_inner + reqShift)%100;
            requestFound_inner = true;
        }
    }

    //outputs
    idToRespondTo_out = requestsToAnswerTo_inner[currentRequestAnswered_inner];
}



void responseToTheRightUserSpread(int& computerID, c_int& input_acc, c_int& output_acc_prev_channel, c_int& output_acc_next_channel, int& output){

    if(std::get<1>(input_acc)==STOP){
        std::get<1>(output_acc_prev_channel) = STOP;
        std::get<1>(output_acc_next_channel) = STOP;
        return;
    }

    c_int id = cpy(input_acc);
    
    if (std::get<0>(input_acc) < 0){
        std::get<0>(id) = -std::get<0>(id);
    }
    c_int returned;
    c_int transmitted;
    if((std::get<0>(input_acc)==0) || (std::get<0>(id) != computerID)){
        std::get<0>(returned) = 0;
        std::get<1>(returned) = REGULAR;

        transmitted = cpy(input_acc);
    } else {
        returned = cpy(input_acc);
        std::get<1>(transmitted) = STOP;
    }

    output_acc_next_channel = cpy(transmitted);
    output_acc_prev_channel = cpy(transmitted);

    output = std::get<1>(returned);
}



void aggregatingRequestsCollect(int input, c_IntArray& requests, c_IntArray& prev_input_requests, c_IntArray& next_input_requests, c_IntArray& prev_output_requests, c_IntArray& next_output_requests, IntArray& output){

    if(input!=0){
        if(input<0){
            std::get<0>(requests)[-input] = input;
        } else {
            std::get<0>(requests)[input] = input;
        }
    }

    for (auto i : range(100)) {
        if(std::get<0>(prev_input_requests)[i]!=0){
            std::get<0>(requests)[i] = std::get<0>(prev_input_requests)[i];
        }
        if(std::get<0>(next_input_requests)[i]!=0){
            std::get<0>(requests)[i] = std::get<0>(next_input_requests)[i];
        }
    }

    next_output_requests = cpy(requests);
    prev_output_requests = cpy(requests);
    output = std::get<0>(requests);
}


void PidControllerInit(double& requested__time_in,double& resulting__time_in,bool& enabled_in,double& derivative_inner,double& integral_inner,double& error_inner,double& dt_inner,double& p_inner,double& i_inner,double& d_inner,int& knob__value_inner,int& min__knob__value_inner,int& max__knob__value_inner,int& knob_out){
    derivative_inner = 0;
    integral_inner = 0;
    error_inner = 0;
    dt_inner = 0;

    p_inner = -1;
    i_inner = -0.01;
    d_inner = 0;

    knob__value_inner = 20;
    min__knob__value_inner = 20;
    max__knob__value_inner = 100;

    knob_out = knob__value_inner;
}

void PidControllerThen(double& requested__time_in,double& resulting__time_in,bool& enabled_in,double& derivative_inner,double& integral_inner,double& error_inner,double& dt_inner,double& p_inner,double& i_inner,double& d_inner,int& knob__value_inner,int& min__knob__value_inner,int& max__knob__value_inner,int& knob_out){

    if (enabled_in){
        dt_inner = resulting__time_in;
        error_inner = requested__time_in - resulting__time_in;
        integral_inner = integral_inner + error_inner * dt_inner;
        derivative_inner = error_inner / dt_inner;
        knob__value_inner = (int) (p_inner*error_inner + i_inner*integral_inner + d_inner*derivative_inner);

        knob__value_inner = std::min(max__knob__value_inner, knob__value_inner);
        knob__value_inner = std::max(min__knob__value_inner, knob__value_inner);
    }
    knob_out = knob__value_inner;
}


void numberOfRespondedRequestsCollect(bool input, c_int& sum, c_int& next_input_sum, c_int& next_output_sum, c_int& prev_input_sum, c_int& prev_output_sum, int& output){
    // if not receiving next, assuming next == default (ie. int sum = 0)
    // same for prev
    std::get<0>(sum) = std::get<0>(sum) + std::get<0>(prev_input_sum) + std::get<0>(next_input_sum);
    if(input){
        std::get<0>(sum) = std::get<0>(sum) + 1;
    }

    output = std::get<0>(sum);
    next_output_sum = cpy(sum);
    prev_output_sum = cpy(sum);
}

void broadcastRedirectionSpread(c_bool& input_acc, c_bool& output_acc_prev_channel, c_bool& output_acc_next_channel, bool& output){
    if(std::get<1>(input_acc)==STOP){
        std::get<1>(output_acc_prev_channel) = STOP;
        std::get<1>(output_acc_next_channel) = STOP;
        return;
    }

    output_acc_next_channel = cpy(input_acc);
    output_acc_prev_channel = cpy(input_acc);
    output = std::get<0>(input_acc);
}


void broadcastDataQtySpread(c_int& input_acc, c_int& output_acc_prev_channel, c_int& output_acc_next_channel, int& output){

    if(std::get<1>(input_acc)==STOP){
        std::get<1>(output_acc_prev_channel) = STOP;
        std::get<1>(output_acc_next_channel) = STOP;
        return;
    }

    output_acc_next_channel = cpy(input_acc);
    output_acc_prev_channel = cpy(input_acc);
    output = std::get<0>(input_acc);
}


void findRightDataProviderSpread(c_int& input_acc_userID, c_int& input_acc_nbJumps, c_int& output_acc_prev_channel_userID, c_int& output_acc_prev_channel_nbJumps, c_int& output_acc_next_channel_userID,c_int& output_acc_next_channel_nbJumps, int& output){

    if(std::get<1>(input_acc_userID)==STOP || std::get<1>(input_acc_nbJumps)==STOP){
        std::get<1>(output_acc_prev_channel_nbJumps) = STOP;
        std::get<1>(output_acc_prev_channel_userID) = STOP;
        std::get<1>(output_acc_next_channel_nbJumps) = STOP;
        std::get<1>(output_acc_next_channel_userID) = STOP;
        return;
    }

    c_int currentBackendTransmittedID;
    c_int nextBackendData;

    if (std::get<0>(input_acc_nbJumps) == (std::get<0>(input_acc_userID)%4)){
        currentBackendTransmittedID = cpy(input_acc_userID);
        std::get<1>(nextBackendData) = STOP;
    }else{
        std::get<0>(input_acc_nbJumps) = std::get<0>(input_acc_nbJumps)+1;
        std::get<0>(currentBackendTransmittedID) = 0;
        nextBackendData = cpy(input_acc_userID);
    }
    
    
    output = std::get<0>(currentBackendTransmittedID);
    output_acc_next_channel_userID = cpy(input_acc_userID); 
    output_acc_next_channel_nbJumps = cpy(input_acc_nbJumps);
    std::get<1>(output_acc_prev_channel_userID) = STOP;
    std::get<1>(output_acc_prev_channel_nbJumps) = STOP;
}