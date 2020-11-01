#pragma once
namespace fw {

    class Event
    {
    public:
        Event();
        virtual ~Event();
        virtual const char* GetType() = 0;


    protected:
        std::string eventType="Event";
    };

}