#include "EventService.h"

EventService::EventService()
    : work_(io_service_)
{
    Start();
}

EventService::~EventService()
{
    Stop();
}

void EventService::Start()
{
    thread_ = std::thread([&]{
        io_service_.run();
    });
}

void EventService::Stop()
{
    io_service_.stop();
    if (thread_.joinable()) {
        thread_.join();
    }
}

void EventService::Subscribe(EventInterface* event, std::function<void(EventInterface*)> handler)
{
    handlers_[event->id()].push_back(handler);    
}

void EventService::Publish(EventInterface* event)
{
    auto topic_iter = handlers_.find(event->id());
    if (topic_iter != handlers_.end()) {
        for (auto handler : topic_iter->second) {
            io_service_.post(std::bind(handler, event));
        }
    }
}

