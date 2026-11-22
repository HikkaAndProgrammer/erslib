#include "erslib/core/async/task.hpp"

#ifdef _HAS_BOOST_ASIO


// boost
#include <boost/asio/post.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/use_awaitable.hpp>

// ers
#include <erslib/core/async/error.hpp>


boost::asio::awaitable<void> ers::impl::yield() {
    auto executor = co_await boost::asio::this_coro::executor;
    co_await boost::asio::post(executor, boost::asio::use_awaitable);
}

ers::AsyncTask<void> ers::impl::checkpoint() {
    co_await yield();

    auto state = co_await boost::asio::this_coro::cancellation_state;

    if (state.cancelled() != boost::asio::cancellation_type::none)
        co_return make_error(ers::EAsyncError::Cancelled, "The job was cancelled.");

    co_return ok;
}


#endif
