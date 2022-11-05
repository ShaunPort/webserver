//
// Created by 袁肖杨 on 2022/11/5.
//


#include "epoller.h"

namespace webserver{

    Epoller::Epoller(int maxEvent) : epollFd_(epoll_create(EPOLL_CREATE_SIZE)), events_(maxEvent){
        assert(epollFd_ >= 0 && events_.size() > 0);
    }

    Epoller::~Epoller() {
        close(epollFd_);
    }

    bool Epoller::AddFd(int fd, uint32_t events) {
        if (fd < 0) {
            return false;
        }
        epoll_event event = {0};
        event.data.fd = fd;
        event.events = events;
        return 0 == epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event);
    }

    bool Epoller::ModFd(int fd, uint32_t events) {
        if (fd < 0) {
            return false;
        }
        epoll_event event = {0};
        event.data.fd = fd;
        event.events = events;
        return 0 == epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &event);
    }

    bool Epoller::DelFd(int fd) {
        if (fd < 0) {
            return false;
        }
        return 0 == epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, 0);
    }

    int32_t Epoller::Wait(int timeoutMs) {
        return epoll_wait(epollFd_, &events_[0], static_cast<int>(events_.size()), timeoutMs);
    }

    int Epoller::GetEventFd(size_t i) const {
        assert(i < events_.size() && i >= 0);
        return events_[i].data.fd;
    }

    uint32_t Epoller::GetEvents(size_t i) const {
        assert(i < events_.size() && i >= 0);
        return events_[i].events;
    }

}
