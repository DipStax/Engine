#ifndef ENG_THREAD_POOL_HPP
#define ENG_THREAD_POOL_HPP

#include <array>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#define MAX_THREAD_TP 5

namespace eng
{
    template<size_t N>
    class ThreadPool
    {
        public:
            ThreadPool(bool _start = false);
            ~ThreadPool();

            void start();
            void stop();

            void enqueue(const std::function<void()> &_job);

        private:
            void threadLoop();

            bool m_terminate = false;
            bool m_isStarted = false;

            std::mutex m_mutex;
            std::condition_variable m_condition;

            std::array<std::thread, N> m_thread;

            std::queue<std::function<void()>> m_job;
    };
}
#include "ThreadPool.inl"

#endif