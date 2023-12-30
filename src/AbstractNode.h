#ifndef LAB6_ABSTRACTNODE_H
#define LAB6_ABSTRACTNODE_H


#include <map>
#include <unistd.h>
#include "zmq.hpp"
#include "ChildNodeInfo.h"
#include <mutex>
#include <utility>
#include "ZmqUtils.h"

using std::to_string;

class AbstractNode 
{
    public:
    // предотвращает неявное преобразование типов
        explicit AbstractNode(int id) : Id(id), Port(ZmqUtils::PORT_TO_BIND_FROM), outerNodes(), context(1), Receiver(context, zmq::socket_type::rep)
        {
            occupyPort();
        }

        AbstractNode() {}

        pid_t addChild(int id, int registerPort) 
        {
            pid_t child = fork(); // дочерний процесс
            if (child == 0) 
            {
                execl("server", to_string(id).c_str(), to_string(Id).c_str(),to_string(Port).c_str(), to_string(registerPort).c_str(), NULL); // запустить процесс
            }
            else if (child < 0)
            { 
                std::cout << "Cannot fork()"; exit(0); 
            }
            return child;
        }

    protected:
        int Id;
        int Port;
        std::map<int, ChildNodeInfo> outerNodes;
        zmq::context_t context; // коллекция объектов
        zmq::socket_t Receiver; // связь узлов

        void occupyPort() // занять порт
        {
            Port = ZmqUtils::occupyPort(Receiver);
        }
};


#endif //LAB6_ABSTRACTNODE_H
