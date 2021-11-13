#ifndef MULTINODE_EXAMPLE_SUBSCRIBER_H
#define MULTINODE_EXAMPLE_SUBSCRIBER_H


#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
    MinimalSubscriber(const std::string & node_name, const std::string & topic_name);

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};


#endif //MULTINODE_EXAMPLE_SUBSCRIBER_H
