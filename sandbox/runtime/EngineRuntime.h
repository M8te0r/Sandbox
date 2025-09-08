#pragma once
#include <chrono>
namespace Elysian
{
    class EngineRuntime
    {
    private:
        std::chrono::steady_clock::time_point lastFrame = std::chrono::steady_clock::now(); // 上一帧时间
        static const float fpsAlpha;                                                        // FPS做线性插值时用的alpha
        float averageDuration = 0.0f;                                                       // 平均时间
        int frameCount = 0;                                                                 // tick次数
        int FPS = 0;                                                                        // fps

    public:
        void startEngine();
        void shutdownEngine();
        void run();

        void tickOneFrame();

    private:
        void render();
        float calculateDeltaTime();
        void calculateFPS(float delta_time);
    };

} // namespace Elysian
