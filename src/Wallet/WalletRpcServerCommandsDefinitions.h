// Copyright (c) 2011-2017, The ManateeCoin Developers, The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once
#include "CryptoNoteProtocol/CryptoNoteProtocolDefinitions.h"
#include "CryptoNoteCore/CryptoNoteBasic.h"
#include "crypto/hash.h"
#include "Rpc/CoreRpcServerCommandsDefinitions.h"
#include "WalletRpcServerErrorCodes.h"

namespace Tools
{
namespace wallet_rpc
{

using CryptoNote::ISerializer;

#define WALLET_RPC_STATUS_OK      "OK"
#define WALLET_RPC_STATUS_BUSY    "BUSY"

struct COMMAND_RPC_GET_ADDRESS
{
	typedef CryptoNote::EMPTY_STRUCT request;

	struct response
	{
		std::string address;

		void serialize(ISerializer& s) {
			KV_MEMBER(address)
		}
	};
};

  struct COMMAND_RPC_GET_BALANCE
  {
    typedef CryptoNote::EMPTY_STRUCT request;

    struct response
    {
      uint64_t locked_amount;
      uint64_t available_balance;

      void serialize(ISerializer& s) {
        KV_MEMBER(locked_amount)
        KV_MEMBER(available_balance)
      }
    };
  };

  struct COMMAND_RPC_GET_BALANCE_XMR
  {
	  typedef CryptoNote::EMPTY_STRUCT request;

	  struct response
	  {
		  uint64_t balance;
		  uint64_t unlocked_balance;

		  void serialize(ISerializer& s) {
			  KV_MEMBER(balance)
		      KV_MEMBER(unlocked_balance)
		  }
	  };
  };

  struct transfer_destination
  {
    uint64_t amount;
    std::string address;

    void serialize(ISerializer& s) {
      KV_MEMBER(amount)
      KV_MEMBER(address)
    }
  };

  struct COMMAND_RPC_TRANSFER
  {
    struct request
    {
      std::list<transfer_destination> destinations;
      uint64_t fee;
      uint64_t mixin;
      uint64_t unlock_time;
      std::string payment_id;

      void serialize(ISerializer& s) {
        KV_MEMBER(destinations)
        KV_MEMBER(fee)
        KV_MEMBER(mixin)
        KV_MEMBER(unlock_time)
        KV_MEMBER(payment_id)
      }
    };

    struct response
    {
      std::string tx_hash;

      void serialize(ISerializer& s) {
        KV_MEMBER(tx_hash)
      }
    };
  };

  struct COMMAND_RPC_TRANSFER_XMR
  {
	  struct request
	  {
		  std::list<transfer_destination> destinations;
		  uint64_t fee = 1000000;
		  uint64_t mixin = 0;
		  uint64_t unlock_time;
		  std::string payment_id;
		  bool get_tx_key = false;
		  uint64_t priority = 0;
		  bool do_not_relay = false;
		  bool get_tx_hex = false;

		  void serialize(ISerializer& s) {
			  KV_MEMBER(destinations)
			  KV_MEMBER(fee)
			  KV_MEMBER(mixin)
			  KV_MEMBER(unlock_time)
			  KV_MEMBER(payment_id)
			  KV_MEMBER(get_tx_key)
			  KV_MEMBER(priority)
			  KV_MEMBER(do_not_relay)
			  KV_MEMBER(get_tx_hex)
		  }
	  };

	  struct response
	  {
		  uint64_t fee;
		  std::string tx_hash;
		  std::string tx_key;
		  std::string tx_blob;

		  void serialize(ISerializer& s) {
			  KV_MEMBER(fee)
			  KV_MEMBER(tx_hash)
			  KV_MEMBER(tx_key)
			  KV_MEMBER(tx_blob)
		  }
	  };
  };

  struct COMMAND_RPC_TRANSFER_SPLIT
  {
	  struct request
	  {
		  std::list<transfer_destination> destinations;
		  uint32_t account_index;
		  std::set<uint32_t> subaddr_indices;
		  uint32_t priority;
		  uint64_t mixin;
		  uint64_t unlock_time;
		  std::string payment_id;
		  bool get_tx_keys;
		  bool do_not_relay;
		  bool get_tx_hex;

		  void serialize(ISerializer& s) {
			KV_MEMBER(destinations)
			KV_MEMBER(account_index)
			KV_MEMBER(subaddr_indices)
			KV_MEMBER(priority)
			KV_MEMBER(mixin)
			KV_MEMBER(unlock_time)
			KV_MEMBER(payment_id)
			KV_MEMBER(get_tx_keys)
			KV_MEMBER(do_not_relay, false)
			KV_MEMBER(get_tx_hex, false)
		  }
	  };

	  struct key_list
	  {
		  std::list<std::string> keys;

		  void serialize(ISerializer& s) {
			  KV_MEMBER(keys)
		  }
	  };

	  struct response
	  {
		  std::list<std::string> tx_hash_list;
		  std::list<std::string> tx_key_list;
		  std::list<uint64_t> amount_list;
		  std::list<uint64_t> fee_list;
		  std::list<std::string> tx_blob_list;

		  void serialize(ISerializer& s) {
			KV_MEMBER(tx_hash_list)
			KV_MEMBER(tx_key_list)
			KV_MEMBER(amount_list)
			KV_MEMBER(fee_list)
			KV_MEMBER(tx_blob_list)
		  }
	  };
  };

  struct COMMAND_RPC_STORE
  {
    typedef CryptoNote::EMPTY_STRUCT request;
    typedef CryptoNote::EMPTY_STRUCT response;
  };

  struct payment_details
  {
    std::string tx_hash;
    uint64_t amount;
    uint64_t block_height;
    uint64_t unlock_time;

    void serialize(ISerializer& s) {
      KV_MEMBER(tx_hash)
      KV_MEMBER(amount)
      KV_MEMBER(block_height)
      KV_MEMBER(unlock_time)
    }
  };

  struct payment_details2
  {
	  std::string payment_id;
	  std::string tx_hash;
	  uint64_t amount;
	  uint64_t block_height;
	  uint64_t unlock_time;

	  void serialize(ISerializer& s) {
		  KV_MEMBER(payment_id)
	      KV_MEMBER(tx_hash)
		  KV_MEMBER(amount)
		  KV_MEMBER(block_height)
		  KV_MEMBER(unlock_time)
	  }
  };


  struct COMMAND_RPC_GET_PAYMENTS
  {
    struct request
    {
      std::string payment_id;

      void serialize(ISerializer& s) {
        KV_MEMBER(payment_id)
      }
    };

    struct response
    {
      std::list<payment_details> payments;

      void serialize(ISerializer& s) {
        KV_MEMBER(payments)
      }
    };
  };

  struct COMMAND_RPC_GET_BULK_PAYMENTS
  {
	  struct request
	  {
		  std::vector<std::string> payment_ids;
		  uint64_t min_block_height;

		  void serialize(ISerializer& s) {
			  KV_MEMBER(payment_ids)
				  KV_MEMBER(min_block_height)
		  }
	  };

	  struct response
	  {
		  std::list<payment_details2> payments;

		  void serialize(ISerializer& s) {
			  KV_MEMBER(payments)
		  }
	  };
  };


  struct Transfer {
    uint64_t time;
    bool output;
    std::string transactionHash;
    uint64_t amount;
    uint64_t fee;
    std::string paymentId;
    std::string address;
    uint64_t blockIndex;
    uint64_t unlockTime;

    void serialize(ISerializer& s) {
      KV_MEMBER(time)
      KV_MEMBER(output)
      KV_MEMBER(transactionHash)
      KV_MEMBER(amount)
      KV_MEMBER(fee)
      KV_MEMBER(paymentId)
      KV_MEMBER(address)
      KV_MEMBER(blockIndex)
      KV_MEMBER(unlockTime)
    }
  };

  struct COMMAND_RPC_GET_TRANSFERS {
    typedef CryptoNote::EMPTY_STRUCT request;

    struct response {
      std::list<Transfer> transfers;

      void serialize(ISerializer& s) {
        KV_MEMBER(transfers)
      }
    };
  };

  struct COMMAND_RPC_GET_HEIGHT {
    typedef CryptoNote::EMPTY_STRUCT request;

    struct response {
      uint64_t height;

      void serialize(ISerializer& s) {
        KV_MEMBER(height)
      }
    };
  };

  struct COMMAND_RPC_RESET {
    typedef CryptoNote::EMPTY_STRUCT request;
    typedef CryptoNote::EMPTY_STRUCT response;
  };
}
}
