/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2021-2022 Micron Technology, Inc. All rights reserved.
 */

#include <assert.h>

#include <hse/hse.h>
#include <jni.h>

#include "com_micron_hse_project_hse_KvdbTransaction.h"
#include "hsejni.h"

jlong
Java_com_micron_hse_1project_hse_KvdbTransaction_alloc(
    JNIEnv *env,
    jclass txn_cls,
    jlong kvdb_handle)
{
    struct hse_kvdb_txn *txn;
    struct hse_kvdb *kvdb = (struct hse_kvdb *)kvdb_handle;

    (void)env;
    (void)txn_cls;

    txn = hse_kvdb_txn_alloc(kvdb);

    return (jlong)txn;
}

void
Java_com_micron_hse_1project_hse_KvdbTransaction_free(
    JNIEnv *env,
    jobject txn_obj,
    jlong kvdb_handle,
    jlong txn_handle)
{
    struct hse_kvdb *kvdb = (struct hse_kvdb *)kvdb_handle;
    struct hse_kvdb_txn *txn = (struct hse_kvdb_txn *)txn_handle;

    (void)env;
    (void)txn_obj;

    hse_kvdb_txn_free(kvdb, txn);
}

void
Java_com_micron_hse_1project_hse_KvdbTransaction_abort(
    JNIEnv *env,
    jobject txn_obj,
    jlong kvdb_handle,
    jlong txn_handle)
{
    hse_err_t err;
    struct hse_kvdb *kvdb = (struct hse_kvdb *)kvdb_handle;
    struct hse_kvdb_txn *txn = (struct hse_kvdb_txn *)txn_handle;

    (void)txn_obj;

    err = hse_kvdb_txn_abort(kvdb, txn);
    if (err)
        throw_new_hse_exception(env, err);
}

void
Java_com_micron_hse_1project_hse_KvdbTransaction_begin(
    JNIEnv *env,
    jobject txn_obj,
    jlong kvdb_handle,
    jlong txn_handle)
{
    hse_err_t err;
    struct hse_kvdb *kvdb = (struct hse_kvdb *)kvdb_handle;
    struct hse_kvdb_txn *txn = (struct hse_kvdb_txn *)txn_handle;

    (void)txn_obj;

    err = hse_kvdb_txn_begin(kvdb, txn);
    if (err)
        throw_new_hse_exception(env, err);
}

void
Java_com_micron_hse_1project_hse_KvdbTransaction_commit(
    JNIEnv *env,
    jobject txn_obj,
    jlong kvdb_handle,
    jlong txn_handle)
{
    hse_err_t err;
    struct hse_kvdb *kvdb = (struct hse_kvdb *)kvdb_handle;
    struct hse_kvdb_txn *txn = (struct hse_kvdb_txn *)txn_handle;

    (void)txn_obj;

    err = hse_kvdb_txn_commit(kvdb, txn);
    if (err)
        throw_new_hse_exception(env, err);
}

jobject
Java_com_micron_hse_1project_hse_KvdbTransaction_getState(
    JNIEnv *env,
    jobject txn_obj,
    jlong kvdb_handle,
    jlong txn_handle)
{
    enum hse_kvdb_txn_state state;
    struct hse_kvdb *kvdb = (struct hse_kvdb *)kvdb_handle;
    struct hse_kvdb_txn *txn = (struct hse_kvdb_txn *)txn_handle;

    (void)env;
    (void)txn_obj;

    state = hse_kvdb_txn_state_get(kvdb, txn);

    switch (state) {
        case HSE_KVDB_TXN_ABORTED:
            return globals.com.micron.hse_project.hse.KvdbTransaction.State.ABORTED;
        case HSE_KVDB_TXN_ACTIVE:
            return globals.com.micron.hse_project.hse.KvdbTransaction.State.ACTIVE;
        case HSE_KVDB_TXN_COMMITTED:
            return globals.com.micron.hse_project.hse.KvdbTransaction.State.COMMITTED;
        case HSE_KVDB_TXN_INVALID:
            return globals.com.micron.hse_project.hse.KvdbTransaction.State.INVALID;
    }

    abort();
}