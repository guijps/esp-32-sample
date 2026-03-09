#ifndef GENERIC_COMMUNICATION_H
#define GENERIC_COMMUNICATION_H
class GenericCommunication
{
    public:
        virtual ~GenericCommunication() {}
        virtual void initialize() = 0;
        virtual void sendData(const char* data) = 0;
        virtual const char* receiveData() = 0;
};
#endif //GENERIC_COMMUNICATION_H