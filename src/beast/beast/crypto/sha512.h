//------------------------------------------------------------------------------
/*
    This file is part of Beast: https://github.com/vinniefalco/Beast
    Copyright 2013, Vinnie Falco <vinnie.falco@gmail.com>

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef BEAST_CRYPTO_SHA512_H_INCLUDED
#define BEAST_CRYPTO_SHA512_H_INCLUDED

#include <beast/hash/endian.h>
#include <beast/utility/noexcept.h>
#include <beast/crypto/impl/sha512_context.h>
#include <array>

namespace beast {

class sha512_hasher
{
public:
    static beast::endian const endian =
        beast::endian::native;

    using result_type =
        std::array<std::uint8_t, 64>;

    sha512_hasher()
    {
        detail::init(ctx_);
    }

    void
    operator()(void const* data,
        std::size_t size) noexcept
    {
        detail::update(ctx_, data, size);
    }

    explicit
    operator result_type() noexcept
    {
        result_type digest;
        finish(ctx_, &digest[0]);
        return digest;
    }

private:
    detail::sha512_context ctx_;
};

// secure version
class sha512_hasher_s
{
public:
    static beast::endian const endian =
        beast::endian::native;

    using result_type =
        std::array<std::uint8_t, 64>;

    sha512_hasher_s()
    {
        init(ctx_);
    }

    ~sha512_hasher_s()
    {
        secure_erase(ctx_);
    }

    void
    operator()(void const* data,
        std::size_t size) noexcept
    {
        update(ctx_, data, size);
    }

    explicit
    operator result_type() noexcept
    {
        result_type digest;
        finish(ctx_, &digest[0]);
        return digest;
    }

private:
    detail::sha512_context ctx_;
};

}

#endif
