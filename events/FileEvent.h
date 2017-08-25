#ifndef FILE_EVENT_H_
#define FILE_EVENT_H_

#include "EventInterface.h"

class FileEvent : public EventInterface {
public:
    enum FileEventType {
        NONE,
        SAVE,
        LOAD
    };
public:
    explicit FileEvent(FileEventType type) : type_(type) {}
    ~FileEvent() {}
    FileEventType GetType() const {
        return type_;
    }
private:
    FileEventType type_;
};

#endif  // FILE_EVENT_H_

