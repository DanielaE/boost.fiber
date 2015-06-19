
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_spinlock

#ifndef BOOST_FIBERS_RECURSIVE_MUTEX_H
#define BOOST_FIBERS_RECURSIVE_MUTEX_H

#include <cstddef>
#include <deque>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#if defined(BOOST_FIBERS_USE_ATOMICS)
# include <boost/fiber/detail/spinlock.hpp>
#endif
#include <boost/fiber/fiber_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL recursive_mutex {
private:
    enum class mutex_status {
        locked = 0,
        unlocked
    };

#if defined(BOOST_FIBERS_USE_ATOMICS)
    detail::spinlock                    splk_;
#endif
    mutex_status                        state_;
    fiber_context::id                   owner_;
    std::size_t                         count_;
    std::deque< fiber_context * >       waiting_;

    bool lock_if_unlocked_();

public:
    recursive_mutex();

    ~recursive_mutex();

    recursive_mutex( recursive_mutex const&) = delete;
    recursive_mutex & operator=( recursive_mutex const&) = delete;

    void lock();

    bool try_lock();

    void unlock();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_RECURSIVE_MUTEX_H
