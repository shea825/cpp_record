//
// Created by shea on 9/29/22.
//

#include <memory>
#include <vector>
#include <iostream>

enum EventType {
    TaskAssignment = 0,
    StageSwitch = 1,
    DismissTask = 2,
    NodeReplace = 3
};

struct Event {
    int type{};
    virtual Event *get() = 0;
};

struct TaskAssignmentEvent : Event {
    std::string taskId;
    std::vector<int> members;
    TaskAssignmentEvent *get() override { return this; }
};

struct StageSwitchEvent : Event {
    std::string stageName;
    StageSwitchEvent *get() override { return this; }
};

struct DismissTaskEvent : Event {
    std::string taskId;
    std::vector<int> members;
    DismissTaskEvent *get() override { return this; }
};

struct NodeReplaceEvent : Event {
    std::string taskId;
    std::vector<int> members;
    NodeReplaceEvent *get() override { return this; }
};

std::shared_ptr<Event> decode() {
    // ...
    return std::make_shared<TaskAssignmentEvent>();
}

void eventHandler(Event* event) {
    switch (event->type) {
        case EventType::TaskAssignment: {
//            taskAssignmentEventHandler(reinterpret_cast<TaskAssignmentEvent *>(event));
            break;
        }
        case EventType::StageSwitch: {
//            stageSwitchEventHandler(reinterpret_cast<StageSwitchEvent *>(event));
            break;
        }
        case EventType::DismissTask: {
//            dismissTaskEventHandler(reinterpret_cast<DismissTaskEvent *>(event));
            break;
        }
        case EventType::NodeReplace: {
//            nodeReplaceEventHandler(reinterpret_cast<NodeReplaceEvent *>(event));
            break;
        }
        default: {
            std::cerr << "unknown event type: " << event->type;
        }
    }
}

int main() {
    Event* p = decode()->get();
    eventHandler(p);
}