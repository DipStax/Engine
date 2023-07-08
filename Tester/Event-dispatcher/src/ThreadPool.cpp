#include "ThreadPool.hpp"

namespace tester
{
    void ThreadPool::start()
    {
        if (m_isStarted)
            return;
        for (size_t it = 0; it < N_THREAD_TP; it++)
            m_thread[it] = std::thread(&ThreadPool::loop);
        m_isStarted = true;
    }

    void ThreadPool::stop()
    {
        if (!m_isStarted)
            return;
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_terminate = true;
        }
        m_cond.notify_all();
        for (size_t it = 0; it < N_THREAD_TP; it++)
            m_thread[it].join();
        m_isStarted = false;
    }

    void ThreadPool::enqueue(Task _task)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_queue.push(_task);
        }
        m_cond.notify_one();
    }

    void ThreadPool::loop()
    {
        Task task;

        while (true) {
            {
                std::unique_lock<std::mutex> lock(m_mutex);

                m_cond.wait(lock, [] () {
                    return !m_queue.empty() || m_terminate;
                });
                if (m_terminate)
                    return;
                task = m_queue.pop_front();
            }
            task();
        }
    }
}