#pragma once



namespace dvc_listener {

    class IWorker {
    public:
        IWorker(){};

        virtual void init() = 0;
        virtual void run() = 0;
        virtual void stop() = 0;

    };
}// namespace dvc_listener