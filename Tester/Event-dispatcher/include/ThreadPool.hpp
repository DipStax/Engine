#pragma once

#include <array>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

#include "tsQueue.hpp"

#ifndef N_THREAD_TP
#define N_THREAD_TP 1
#endif

namespace tester
{
    class ThreadPool
    {
        public:
            using Task = std::function<void()>;

            static void start();
            static void stop();

            static void enqueue(Task _task);

        private:
            inline static bool m_isStarted = false;
            inline static bool m_terminate = false;

            inline static ts::Queue<Task> m_queue{};

            inline static std::array<std::thread, N_THREAD_TP> m_thread;
            inline static std::mutex m_mutex;
            inline static std::condition_variable m_cond;

            static void loop();
    };
}