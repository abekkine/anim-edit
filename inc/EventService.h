#ifndef EVENT_SERVICE_H_
#define EVENT_SERVICE_H_

#include <boost/asio.hpp>

#include <string>
#include <thread>
#include <unordered_map>
#include <functional>

#include "EventInterface.h"

class EventService {
public:
    static EventService& instance() {
        static EventService instance_;
        return instance_;
    }
public:
    void Start();
    void Stop();
    void Subscribe(std::string topic, std::function<void(EventInterface*)> handler);
    void Publish(std::string topic, EventInterface* event);

private:
    EventService();
    ~EventService();

private:
    boost::asio::io_service io_service_;
    boost::asio::io_service::work work_;
    std::thread thread_;
    std::unordered_map<std::string, std::vector<std::function<void(EventInterface*)>>> handlers_;
};

#define EVENTS EventService::instance()

#endif // EVENT_SERVICE_H_

