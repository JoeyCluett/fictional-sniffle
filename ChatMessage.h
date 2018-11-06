#ifndef __CPJL_MSG_ChatMessage__
#define __CPJL_MSG_ChatMessage__

#include <string>
#include <CPJL.hpp>
#include <CPJL_Message.hpp>
#include <Topic.hpp>

class ChatMessage : public CPJL_Message {
public:

    int flags;
    std::string sender;
    std::string msg;
    Topic topic;

    ChatMessage(CPJL* cpjl, std::string& topic_name, F_Ptr callback)
         : CPJL_Message(cpjl, topic_name, callback) {

        topic.add(Topic::INT).add(Topic::STRING).add(Topic::STRING).done();
        topic.request(*cpjl, topic_name);
    }

    ChatMessage(CPJL* cpjl, std::string& topic_name)
         : CPJL_Message(cpjl, topic_name) {

        topic.add(Topic::INT).add(Topic::STRING).add(Topic::STRING).done();
        topic.broadcast(*cpjl, topic_name);
    }

    void putMessage(void) override {
        __cpjl->putString(this->topic_name);
        __cpjl->putInt(flags);
        __cpjl->putString(sender);
        __cpjl->putString(msg);
    }

    void getMessage(void) override {
        flags = __cpjl->getInt();
        sender = __cpjl->getString();
        msg = __cpjl->getString();
    }

};

#endif // __CPJL_MSG_ChatMessage__
