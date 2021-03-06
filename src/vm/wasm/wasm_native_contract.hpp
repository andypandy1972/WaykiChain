#pragma once

#include "wasm/wasm_context.hpp"
#include "wasm/types/asset.hpp"
#include "wasm/modules/dex_contract.hpp"

using namespace std;
using namespace wasm;

namespace wasm {

    using transfer_data_type = std::tuple <uint64_t, uint64_t, wasm::asset, string >;
    using set_code_data_type = std::tuple<uint64_t, string, string, string>;

    void wasmio_native_setcode( wasm_context & );
    void wasmio_bank_native_transfer( wasm_context & );

    // inline bool is_native_contract(uint64_t contract){
    //     if(contract == wasmio ||
    //        contract == wasmio_bank)
    //         return true;
    //     return false;
    // }

    inline void sub_balance(CAccount& owner, const wasm::asset& quantity, CAccountDBCache &database){

        string symbol     = quantity.sym.code().to_string();
        uint8_t precision = quantity.sym.precision();
        CHAIN_ASSERT( precision == 8,
                      account_access_exception,
                      "The precision of system coin %s must be %d",
                      symbol, 8)

        CHAIN_ASSERT( owner.OperateBalance(symbol, BalanceOpType::SUB_FREE, quantity.amount),
                      account_access_exception,
                      "Operate account %s failed",
                      owner.nickid.ToString())

        CHAIN_ASSERT( database.SetAccount(owner.regid, owner), account_access_exception,
                      "Save account error")
    }

    inline void add_balance(CAccount& owner, const wasm::asset& quantity, CAccountDBCache &database){

        string symbol     = quantity.sym.code().to_string();
        uint8_t precision = quantity.sym.precision();
        CHAIN_ASSERT( precision == 8,
                      account_access_exception,
                      "The precision of system coin %s must be %d",
                      symbol, 8)

        CHAIN_ASSERT( owner.OperateBalance(symbol, BalanceOpType::ADD_FREE, quantity.amount),
                      account_access_exception,
                      "Operate account %s failed",
                      owner.nickid.ToString().c_str())

        CHAIN_ASSERT( database.SetAccount(owner.regid, owner), account_access_exception,
                      "Save account error")
    }

};