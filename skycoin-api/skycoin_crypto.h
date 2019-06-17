/*
 * This file is part of the Skycoin project, https://skycoin.net/
 *
 * Copyright (C) 2018-2019 Skycoin Project
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SKYCOIN_CRYPTO_H
#define SKYCOIN_CRYPTO_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define SKYCOIN_PUBKEY_LEN 33
#define SKYCOIN_SECKEY_LEN 32
#define SKYCOIN_SIG_LEN 65
#define SKYCOIN_ADDRESS_CHECKSUM_LENGTH 4

typedef struct TransactionOutput {
    uint64_t coin;
    uint64_t hour;
    uint8_t address[20];
} TransactionOutput;

typedef struct Transaction {
    uint8_t nbIn;
    uint8_t nbOut;
    uint8_t inAddress[8][32];
    TransactionOutput outAddress[8];
    int has_innerHash;
    uint8_t innerHash[32];
} Transaction;

void transaction_initZeroTransaction(Transaction* self);
void transaction_addInput(Transaction* self, uint8_t* address);
void transaction_addOutput(Transaction* self, uint32_t coin, uint32_t hour, char* address);
void transaction_innerHash(Transaction* self);
void transaction_msgToSign(Transaction* self, uint8_t index, uint8_t* signature);

void ecdh(const uint8_t* secret_key, const uint8_t* remote_public_key, uint8_t* ecdh_key /*should be size SHA256_DIGEST_LENGTH*/);
void ecdh_shared_secret(const uint8_t* secret_key, const uint8_t* remote_public_key, uint8_t* shared_secret /*should be size SHA256_DIGEST_LENGTH*/);
void secp256k1sum(const uint8_t* seed, const size_t seed_length, uint8_t* digest);
void generate_deterministic_key_pair_iterator(const uint8_t* seed, const size_t seed_length, uint8_t* nextSeed, uint8_t* seckey, uint8_t* pubkey);
void compute_sha256sum(const uint8_t* seed, uint8_t* digest /*size SHA256_DIGEST_LENGTH*/, size_t seed_length);
void add_sha256(const uint8_t* msg1, size_t msg1_len, const uint8_t* msg2, size_t msg2_len, uint8_t* out_digest);
void generate_pubkey_from_seckey(const uint8_t* seckey, uint8_t* pubkey);
void generate_deterministic_key_pair(const uint8_t* seed, const size_t seed_length, uint8_t* seckey, uint8_t* pubkey);
void generate_skycoin_address_from_pubkey(const uint8_t* pubkey, char* address, size_t* size_address);
int ecdsa_skycoin_sign(const uint8_t* priv_key, const uint8_t* digest, uint8_t* sig);
void tohex(char* str, const uint8_t* buffer, int bufferLength);
/**
 * @brief tobuff convert from hexadecimal to a binary buffer
 * @param str input hexadecimal
 * @param buf output binary buffer
 * @param bufferLength len of the output buf, len(buf) * 2 == len(str)
 * @return true if succes, false for error
 */
bool tobuff(const char* str, uint8_t* buf, size_t bufferLength);
void writebuf_fromhexstr(const char* str, uint8_t* buf);

/**
 * @brief verify_pub_key ec secp256k1
 * @param pub_key pub key to b verified
 * @return true if the verification success
 */
bool verify_pub_key(const uint8_t* pub_key);

#endif
