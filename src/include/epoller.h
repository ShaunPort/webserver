//
// Created by 袁肖杨 on 2022/11/5.
//

#ifndef WEBSERVER_EPOLLER_H
#define WEBSERVER_EPOLLER_H


#include <sys/epoll.h> //epoll_ctl()
#include <fcntl.h>  // fcntl()
#include <unistd.h> // close()
#include <assert.h> // close()
#include <vector>
#include <errno.h>

namespace webserver {

#define EPOLL_CREATE_SIZE 512

    class Epoller {
    public:
        /**
         * epoll创建 内核事件注册
         * @param maxEvent 最大内核事件注册数量，默认1024
         */
        explicit Epoller(int maxEvent = 1024);

        /**
         * 关闭内核事件事件表描述符
         */
        ~Epoller();

        /**
         * 往内核事件表中添加文件描述符事件
         * @param fd 文件描述符
         * @param events 指定会被触发的事件，使用枚举类型EPOLL_EVENTS
         * @return true 成功
         */
        bool AddFd(int fd, uint32_t events);

        /**
         * 修改已存在的文件描述符的事件
         * @param fd 已被注册事件的文件描述符
         * @param events 指定会被触发的事件，使用枚举类型EPOLL_EVENTS
         * @return true 成功
         */
        bool ModFd(int fd, uint32_t events);

        /**
         * 撤销注册的文件描述符事件
         * @param fd 已被注册事件的文件描述符
         * @return true 成功
         */
        bool DelFd(int fd);

        /**
         * 监听事件，此时它会等待
         * @param timeoutMs 等待时间，超时返回-1
         * @return 成功时返回就绪的文件描述符的个数
         */
        int Wait(int timeoutMs = -1);

        /**
         * 获取触发事件后，第i个文件描述符
         * @param i 索引
         * @return 文件描述符
         */
        int GetEventFd(size_t i) const;

        /**
         * 获取第i个文件描述符的触发事件符
         * @param i
         * @return 触发事件符
         */
        uint32_t GetEvents(size_t i) const;

    private:
        int epollFd_;

        std::vector<struct epoll_event> events_;
    };
}


#endif //WEBSERVER_EPOLLER_H
