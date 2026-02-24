#include "ChipsFunctions.hpp"
#include <algorithm>
#include <cmath>


void UserMachineInit(chips_int& httpResponse_in, int& startTime_in, int& endTime_in, int& id_in, int& maxNbData_in, int& computerID_ctx, bool& active_inner, bool& waiting__inner, int& time_inner, bool& requiresAuth_inner, bool& newPage_inner, int&currentRequest_inner, int& httpRequest_inner, int& lastRequest_inner, int& fromUserToInternet_out){

    // default values :
    maxNbData_in = 10;
    

    active_inner = false;
    waiting__inner = false;
    time_inner = 0;
    requiresAuth_inner = false;
    newPage_inner = false;

    //nb of data requested
    currentRequest_inner = 0; 

     // (auth ? -1 : 1)*((maxNbData+1)*ID + nbData) with nbData in [1, maxNbData]
    httpRequest_inner = 0;
    lastRequest_inner = 0;
    // outputs
    fromUserToInternet_out = httpRequest_inner;
}

void UserMachineThen(chips_int& httpResponse_in, int& startTime_in, int& endTime_in, int& id_in, int& maxNbData_in, int& computerID_ctx, bool& active_inner, bool& waiting__inner, int& time_inner, bool& requiresAuth_inner, bool& newPage_inner, int&currentRequest_inner, int& httpRequest_inner, int& lastRequest_inner, int& fromUserToInternet_out){
    computerID_ctx = id_in;
    newPage_inner = httpResponse_in !=0 && is_fresh(httpResponse_in);
    requiresAuth_inner = (httpResponse_in < 0) || requiresAuth_inner;
    active_inner = (time_inner>=startTime_in) && (time_inner<endTime_in);
    if (!active_inner) {
        httpRequest_inner = 0;
    } else {
        if (!waiting__inner){
            currentRequest_inner = (int)(randomdouble()*(maxNbData_in-1))+1;
            httpRequest_inner = maxNbData_in*(computerID_ctx-1) + currentRequest_inner;
            if(requiresAuth_inner){
                httpRequest_inner = -httpRequest_inner;
            }
            waiting__inner = true;
        } else {
            if (newPage_inner){
                if(requiresAuth_inner){
                    currentRequest_inner = (int)(randomdouble()*(maxNbData_in-1))+1;
                    httpRequest_inner = -(maxNbData_in*(computerID_ctx-1) + currentRequest_inner);
                    waiting__inner = true;
                }else{
                    waiting__inner = false;
                    httpRequest_inner = 0;
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

void ServerMachineInit(intarray& fromInternet_in, int& wpServed_in, int& maxNbData_in, int& httpResponse_inner, int& currentRequest_inner, bool& requestFound_inner, intarray& requestList_inner, int& nbDataToOutput_inner, int& userIDToOutput_inner, bool& userAuthToOutput_inner, int& fromServerToInternet_out, int& nbData_out, int& userID_out, bool& userAuth_out){
    // default values :
    maxNbData_in = 10;

    httpResponse_inner = 0;
    currentRequest_inner = 0;
    requestFound_inner = false;

    requestList_inner = zeros(100);
}

void ServerMachineThen(intarray& fromInternet_in, int& wpServed_in, int& maxNbData_in, int& httpResponse_inner, int& currentRequest_inner, bool& requestFound_inner, intarray& requestList_inner, int& nbDataToOutput_inner, int& userIDToOutput_inner, bool& userAuthToOutput_inner, int& fromServerToInternet_out, int& nbData_out, int& userID_out, bool& userAuth_out){

    ////////////////// treating client requests one by one
    requestList_inner[currentRequest_inner] = 0;

    for (auto i : range(100)) {
        if(fromInternet_in[i]!=0){
            requestList_inner[i] = fromInternet_in[i];
        }
    }
    requestFound_inner = false;
    for (auto reqShift : range(100)) { // weird way to do it to avoid starvation of clients
        if ( !requestFound_inner && (requestList_inner[(currentRequest_inner + reqShift)%100] != 0)) {
            requestFound_inner = true;
            currentRequest_inner = (currentRequest_inner + reqShift)%100;
        }
    }

    ////////////////// treating server responses one by one
    httpResponse_inner = wpServed_in;

    // outputs
    if(requestFound_inner){
        userAuthToOutput_inner = requestList_inner[currentRequest_inner]<0;
        if(userAuthToOutput_inner){
            nbDataToOutput_inner = (-requestList_inner[currentRequest_inner])%(maxNbData_in);
            userIDToOutput_inner = (-requestList_inner[currentRequest_inner])/(maxNbData_in)+1;
        }else{
            nbDataToOutput_inner = requestList_inner[currentRequest_inner]%(maxNbData_in);
            userIDToOutput_inner = requestList_inner[currentRequest_inner]/(maxNbData_in)+1;
        }
    } else {
        nbDataToOutput_inner = 0;
        userIDToOutput_inner = 0;
        userAuthToOutput_inner = false;
    }

    fromServerToInternet_out = httpResponse_inner;
    userAuth_out = userAuthToOutput_inner;
    nbData_out = nbDataToOutput_inner;
    userID_out = userIDToOutput_inner;
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

void AuthenticatorInit(bool& authProvided_in, bool& isAuthenticated_out){
    // outputs
    isAuthenticated_out = authProvided_in;
}
void AuthenticatorThen(bool& authProvided_in, bool& isAuthenticated_out){
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

void RequestLimiterInit(bool& redirection_in, int& maxRequests_in, int& userID_in, int& nbDataToFetch_in, int& nbAnsweredReqs_in, int& currentNbRequests_inner, bool& redirection_out, chips_int& userID_out, int& dataQty_out){
    currentNbRequests_inner = 0;

    //outputs
    redirection_out = redirection_in;
    assign(userID_out,userID_in);
    dataQty_out = nbDataToFetch_in;
}
void RequestLimiterThen(bool& redirection_in, int& maxRequests_in, int& userID_in, int& nbDataToFetch_in, int& nbAnsweredReqs_in, int& currentNbRequests_inner, bool& redirection_out, chips_int& userID_out, int& dataQty_out){
    
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
    assign(userID_out,userID_in);
    dataQty_out = nbDataToFetch_in;
}


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

    found_inner = false;
    if (requestedData_in > 0){
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

void DataProviderInit(bool& redirection_in, chips_int& userID_in, int& dataQty_in, bool& cacheResponse_in, int& maxDifferentData_inner, int& maxUserID_inner, intarray& dataPerUserID_inner, int& currentlyTreatedUserRequest_inner, int& idToRespondTo_inner, int& dataToFetch_inner, double& time_inner, bool& cacheSearching_inner, bool& oneLessPendingRequest_inner, int& userID_out, int& cacheRequest_out, bool& oneLessPendingRequest_out, double& timeSpentOnReq_out, bool& enableTimeReading_out){
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
void DataProviderThen(bool& redirection_in, chips_int& userID_in, int& dataQty_in, bool& cacheResponse_in, int& maxDifferentData_inner, int& maxUserID_inner, intarray& dataPerUserID_inner, int& currentlyTreatedUserRequest_inner, int& idToRespondTo_inner, int& dataToFetch_inner, double& time_inner, bool& cacheSearching_inner, bool& oneLessPendingRequest_inner, int& userID_out, int& cacheRequest_out, bool& oneLessPendingRequest_out, double& timeSpentOnReq_out, bool& enableTimeReading_out){
    if(oneLessPendingRequest_inner){
        time_inner = 0.0;
    }
    oneLessPendingRequest_inner = false;
    idToRespondTo_inner = 0;
    if((userID_in != 0) && is_fresh(userID_in)){
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
            idToRespondTo_inner = (currentlyTreatedUserRequest_inner +1)%maxUserID_inner;
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
    oneLessPendingRequest_inner = oneLessPendingRequest_inner || (redirection_in && (userID_in != 0) && is_fresh(userID_in));

    // outputs
    userID_out = idToRespondTo_inner; // already formatted as the http answer
    cacheRequest_out = dataToFetch_inner;
    oneLessPendingRequest_out = oneLessPendingRequest_inner;
    timeSpentOnReq_out = time_inner;
    enableTimeReading_out = oneLessPendingRequest_inner;
}


void allDataProvidersOutputsCollect(int& input, collective_intarray& answers, collective_intarray& prev_input_answers, collective_intarray& next_input_answers, collective_intarray& prev_output_answers, collective_intarray& next_output_answers, intarray& output){
    
    collective_intarray temp = cpy(answers);
    if(input!=0){
        if(input>0){
            std::get<0>(temp)[input-1] = input;
        } else {
            std::get<0>(temp)[-input-1] = input;
        }
    }
    for (auto i : range(100)) {
        if(std::get<0>(prev_input_answers)[i]!=0){
            std::get<0>(temp)[i] = std::get<0>(prev_input_answers)[i];
        }
        if(std::get<0>(next_input_answers)[i]!=0){
            std::get<0>(temp)[i] = std::get<0>(next_input_answers)[i];
        }
    }

    next_output_answers = cpy(temp);
    prev_output_answers = cpy(temp);
    output = std::get<0>(temp);
}


void WebPageServiceInit(intarray& respondToThisIDs_in, int& currentRequestAnswered_inner, intarray& requestsToAnswerTo_inner, bool& requestFound_inner, int& idToRespondTo_out){

    currentRequestAnswered_inner = 0;
    requestsToAnswerTo_inner = zeros(100);
    requestFound_inner = false;

    //outputs
    idToRespondTo_out = requestsToAnswerTo_inner[currentRequestAnswered_inner];
}
void WebPageServiceThen(intarray& respondToThisIDs_in, int& currentRequestAnswered_inner, intarray& requestsToAnswerTo_inner, bool& requestFound_inner, int& idToRespondTo_out){

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



void responseToTheRightUserSpread(int& computerID, collective_int& input_acc, collective_int& output_acc_prev_channel, collective_int& output_acc_next_channel, chips_int& output){

    if(std::get<1>(input_acc)==STOP){
        std::get<1>(output_acc_prev_channel) = STOP;
        std::get<1>(output_acc_next_channel) = STOP;
        return;
    }

    collective_int id = cpy(input_acc);
    
    if (std::get<0>(input_acc) < 0){
        std::get<0>(id) = -std::get<0>(id);
    }
    collective_int returned;
    collective_int transmitted;
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

    assign(output,returned);
}



void aggregatingRequestsCollect(int& input, collective_intarray& requests, collective_intarray& prev_input_requests, collective_intarray& next_input_requests, collective_intarray& prev_output_requests, collective_intarray& next_output_requests, intarray& output){
    collective_intarray temp = cpy(requests);

    // Magic const that I think of adding just righ now for a proper indexing system
    // It would take too much time to correct the whole model to get this value propoerly 
    int maxNbData = 10; 
    if(input!=0){
        if(input<0){
            std::get<0>(temp)[-input/maxNbData] = input;
        } else {
            std::get<0>(temp)[input/maxNbData] = input;
        }
    }
    // if(input!=0){
    //     if(input<0){
    //         std::get<0>(temp)[(-input)] = input;
    //     } else {
    //         std::get<0>(temp)[input] = input;
    //     }
    // }

    for (auto i : range(100)) {
        if(std::get<0>(prev_input_requests)[i]!=0){
            std::get<0>(temp)[i] = std::get<0>(prev_input_requests)[i];
        }
        if(std::get<0>(next_input_requests)[i]!=0){
            std::get<0>(temp)[i] = std::get<0>(next_input_requests)[i];
        }
    }

    next_output_requests = cpy(temp);
    prev_output_requests = cpy(temp);
    output = std::get<0>(temp);
}


void PidControllerInit(double& requested__time_in,double& resulting__time_in,bool& enabled_in,double& derivative_inner,double& integral_inner,double& error_inner,double& dt_inner,double& p_inner,double& i_inner,double& d_inner,int& knob__value_inner,int& min__knob__value_inner,int& max__knob__value_inner,int& knob_out){
    derivative_inner = 0;
    integral_inner = 0;
    error_inner = 0;
    dt_inner = 0;

    p_inner = -1;
    i_inner = -0.04;
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


void numberOfRespondedRequestsCollect(bool& input, collective_int& sum, collective_int& prev_input_sum, collective_int& next_input_sum, collective_int& prev_output_sum, collective_int& next_output_sum, int& output){
    collective_int temp = cpy(sum);
    std::get<0>(temp) = std::get<0>(temp) + std::get<0>(prev_input_sum) + std::get<0>(next_input_sum);
    if(input){
        std::get<0>(temp) = std::get<0>(temp) + 1;
    }

    output = std::get<0>(temp);
    next_output_sum = cpy(temp);
    prev_output_sum = cpy(temp);
}

void broadcastRedirectionSpread(collective_bool& input_acc, collective_bool& output_acc_prev_channel, collective_bool& output_acc_next_channel, bool& output){
    if(std::get<1>(input_acc)==STOP){
        std::get<1>(output_acc_prev_channel) = STOP;
        std::get<1>(output_acc_next_channel) = STOP;
        return;
    }

    output_acc_next_channel = cpy(input_acc);
    output_acc_prev_channel = cpy(input_acc);
    output = std::get<0>(input_acc);
}


void broadcastDataQtySpread(collective_int& input_acc, collective_int& output_acc_prev_channel, collective_int& output_acc_next_channel, int& output){

    if(std::get<1>(input_acc)==STOP){
        std::get<1>(output_acc_prev_channel) = STOP;
        std::get<1>(output_acc_next_channel) = STOP;
        return;
    }

    output_acc_next_channel = cpy(input_acc);
    output_acc_prev_channel = cpy(input_acc);
    output = std::get<0>(input_acc);
}


void findRightDataProviderSpread(collective_int& input_acc_userID, collective_int& input_acc_nbJumps, collective_int& output_acc_prev_channel_userID, collective_int& output_acc_prev_channel_nbJumps, collective_int& output_acc_next_channel_userID,collective_int& output_acc_next_channel_nbJumps, chips_int& output){

    if((std::get<1>(input_acc_userID)==STOP) || (std::get<1>(input_acc_nbJumps)==STOP)){
        std::get<1>(output_acc_prev_channel_nbJumps) = STOP;
        std::get<1>(output_acc_prev_channel_userID) = STOP;
        std::get<1>(output_acc_next_channel_nbJumps) = STOP;
        std::get<1>(output_acc_next_channel_userID) = STOP;
        return;
    }

    collective_int currentBackendTransmittedID;
    collective_int nextBackendData;

    if (std::get<0>(input_acc_nbJumps) == (std::get<0>(input_acc_userID)%4)){
        currentBackendTransmittedID = cpy(input_acc_userID);
        std::get<1>(nextBackendData) = STOP;
    }else{
        std::get<0>(input_acc_nbJumps) = std::get<0>(input_acc_nbJumps)+1;
        std::get<0>(currentBackendTransmittedID) = 0;
        nextBackendData = cpy(input_acc_userID);
    }
    
    
    assign(output,currentBackendTransmittedID);
    output_acc_next_channel_userID = cpy(nextBackendData); 
    output_acc_next_channel_nbJumps = cpy(input_acc_nbJumps);
    std::get<1>(output_acc_prev_channel_userID) = STOP;
    std::get<1>(output_acc_prev_channel_nbJumps) = STOP;
}