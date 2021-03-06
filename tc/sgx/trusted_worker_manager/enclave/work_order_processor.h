/* Copyright 2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include <string>
#include <vector>
#include "enclave_data.h"

#include "parson.h"
#include "types.h"
#include "work_order_data_handler.h"

namespace tcf {
        class WorkOrderProcessor {
        public:
                WorkOrderProcessor() {}
                ByteArray CreateErrorResponse(int err_code, const char* err_message);
                ByteArray Process(EnclaveData& enclaveData, std::string json_str);

        private:
                void ParseJsonInput(EnclaveData& enclaveData, std::string json_str);
                ByteArray CreateJsonOutput();
                std::vector<tcf::WorkOrderData> ExecuteWorkOrder();
                ByteArray ComputeRequestHash();
                ByteArray ResponseHashCalculate(std::vector<tcf::WorkOrderData>& wo_data);
                tcf_err_t VerifyEncryptedRequestHash();
                int VerifyRequesterSignature();
                void ComputeSignature(EnclaveData& enclaveData, ByteArray& message_hash);
                void ConcatHash(ByteArray& dst, ByteArray& src);
                /***Required for work order processing **/
                std::string tc_service_address;
                std::string participant_address;
                /***************************************/

                std::vector<WorkOrderDataHandler> data_items_in;
                std::vector<WorkOrderDataHandler> data_items_out;

                int response_timeout_msecs;
                std::string payload_format;
                std::string result_uri;
                std::string notify_uri;
                std::string work_order_id;
                std::string worker_id;
                std::string workload_id;
                std::string requester_id;
                std::string worker_encryption_key;
                std::string data_encryption_algorithm;
                std::string encrypted_session_key;
                std::string session_key_iv;
                std::string requester_nonce;
                std::string encrypted_request_hash;
                std::string requester_signature;
                int json_request_id;
                std::string worker_nonce;
                std::string worker_signature;
                ByteArray session_key = {};

                /** TODO: Temp Implementation **/
                /** verifying_key is client's public key used for signature verification.
                    Sharing keys between client and worker is not defined in spec yet.
                    For now, client's public key is shared in the workorder request.
                **/
                std::string verifying_key;
        };
}  // namespace tcf
