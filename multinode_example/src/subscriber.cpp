#include "subscriber.h"

#include <sstream>

MinimalSubscriber::MinimalSubscriber(const std::string & node_name, const std::string & topic_name)
                                    : Node(node_name)
{
    subscription_ = this->create_subscription<std_msgs::msg::String>(
            topic_name, 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
}


void MinimalSubscriber::topic_callback(const std_msgs::msg::String::SharedPtr msg) const
{
    std::ostringstream ss;
    ss << std::this_thread::get_id();

    RCLCPP_INFO(this->get_logger(), "I heard: '%s', threaid: '%s'", msg->data.c_str(), ss.str().c_str());
}

