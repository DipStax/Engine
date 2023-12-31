#pragma once

#include <array>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

#include "Engine/Container/tsQueue.hpp"
#include "Tool/Export.hpp"

#ifndef N_THREAD_TP
#define N_THREAD_TP 1
#endif

namespace eng
{
    class PROJECT_API ThreadPool
    {
        public:
            using Task = std::function<void()>;

            ThreadPool();
            ~ThreadPool();

            void start();
            void stop();

            void enqueue(Task _task);

            [[nodiscard]] bool empty();

        private:
            bool m_isStarted = false;
            bool m_terminate = false;

            ts::Queue<Task> m_queue{};

            std::array<std::thread, N_THREAD_TP> m_thread;
            std::mutex m_mutex;
            std::condition_variable m_cond;

            void loop();
    };
}