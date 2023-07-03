#include "ThreadPool.hpp"

namespace eng
{
    template<size_t N>
    ThreadPool<N>::ThreadPool(bool _start)
    {
        if (_start)
            start();
    }

    template<size_t N>
    ThreadPool<N>::~ThreadPool()
    {
        stop();
    }

    template<size_t N>
    void ThreadPool<N>::start()
    {
        if (m_isStarted)
            return;
        for (size_t i = 0; i < N; i++)
            m_thread[i] = std::thread([&]() { threadLoop(); });
        m_isStarted = true;
    }

    template<size_t N>
    void ThreadPool<N>::stop()
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_terminate = true;
        }
        m_condition.notify_all();
        for (std::thread &_thread : m_thread)
            _thread.join();
        m_isStarted = false;
    }

    template<size_t N>
    void ThreadPool<N>::enqueue(const std::function<void()> &_job)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_job.push(_job);
        }
        m_condition.notify_one();
    }

    template<size_t N>
    void ThreadPool<N>::threadLoop()
    {
        std::function<void()> job;

        while (true) {
            {
                std::unique_lock<std::mutex> lock(m_mutex);

                m_condition.wait(lock, [this] {
                    return !m_job.empty() || m_terminate;
                });
                if (m_terminate)
                    return;
                job = m_job.front();
                m_job.pop();
            }
            job();
        }
    }
}