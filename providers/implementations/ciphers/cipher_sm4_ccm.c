/*
 * Copyright 2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/* Dispatch functions for SM4 CCM mode */

#include "cipher_sm4_ccm.h"
#include "prov/implementations.h"
#include "prov/providercommon.h"

static OSSL_FUNC_cipher_freectx_fn sm4_ccm_freectx;

static void *sm4_ccm_newctx(void *provctx, size_t keybits)
{
    PROV_SM4_CCM_CTX *ctx;

    if (!ossl_prov_is_running())
        return NULL;

    ctx = OPENSSL_zalloc(sizeof(*ctx));
    if (ctx != NULL)
        ossl_ccm_initctx(&ctx->base, keybits, ossl_prov_sm4_hw_ccm(keybits));
    return ctx;
}

static void *sm4_ccm_dupctx(void *provctx)
{
    PROV_SM4_CCM_CTX *ctx = provctx;

    if (ctx == NULL)
        return NULL;
    return OPENSSL_memdup(ctx, sizeof(*ctx));
}

static void sm4_ccm_freectx(void *vctx)
{
    PROV_SM4_CCM_CTX *ctx = (PROV_SM4_CCM_CTX *)vctx;

    OPENSSL_clear_free(ctx,  sizeof(*ctx));
}

/* sm4128ccm functions */
IMPLEMENT_aead_cipher(sm4, ccm, CCM, AEAD_FLAGS, 128, 8, 96);
