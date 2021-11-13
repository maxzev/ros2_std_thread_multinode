#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "subscriber.h"


// Good explanation is here:
//https://answers.ros.org/question/310066/ros2-best-practices-multiple-nodes-in-the-same-process/

// Test it with this command: ros2 topic pub /topic1 std_msgs/String "data: abc" -1
// Replacing /topic1 with /topic2, /topic3, /topic4 you will see thread number of executor.

void t1_spin()
{
    // Creates two nodes to be run in one thread together.
    rclcpp::executors::SingleThreadedExecutor exec;

    auto subscriber1 = std::make_shared<MinimalSubscriber>("subscriber1", "topic1");
    exec.add_node(subscriber1);
    auto subscriber2 = std::make_shared<MinimalSubscriber>("subscriber2", "topic2");
    exec.add_node(subscriber2);

    // spin will block until the work comes in, execute work as it becomes available, and keep blocking.
    // It will only be interrupted by Ctrl-C.
    exec.spin();
}

void t2_spin()
{
    // Creates two more nodes to be run in another thread.
    rclcpp::executors::SingleThreadedExecutor exec;

    auto subscriber1 = std::make_shared<MinimalSubscriber>("subscriber3", "topic3");
    exec.add_node(subscriber1);
    auto subscriber2 = std::make_shared<MinimalSubscriber>("subscriber4", "topic4");
    exec.add_node(subscriber2);

    exec.spin();
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    std::thread th1(&t1_spin);
    std::thread th2(&t2_spin);

    th1.join();
    th2.join();

    rclcpp::shutdown();

    return 0;
}