#pragma once
namespace Elysian
{
    // 软件运行过程中，需要记录的有什么呢？前述已经提到，
    // 关键变量的值、运行的位置（哪个文件、哪个函数、哪一行）、时间、线程号、进程号。
    // 本文Jungle采用C++设计了LOG类，介绍LOG类的设计之前，需要提及的是log的级别和log位置。

    // 日志级别
    enum LOGLEVEL
    {
        LOG_LEVEL_NONE,
        LOG_LEVEL_ERROR,   // error
        LOG_LEVEL_WARNING, // warning
        LOG_LEVEL_DEBUG,   // debug
        LOG_LEVEL_INFO,    // info
    };

    // 日志输出位置
    enum LOGTARGET
    {
        LOG_TARGET_NONE = 0x00,
        LOG_TARGET_CONSOLE = 0x01,
        LOG_TARGET_FILE = 0x10
    };

    class LogSystem final
    {
    public:
        void initialize();
        void finalize();
    };

} // namespace Elysian
