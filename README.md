Example shows how to manage ros2 nodes using std::threads.

The idea is to have two threads, each of which contains 2 nodes. Every node contains MinimalSubscriber from ros2 examples that can be replaced with actions or service.
The goal is to keep is your business logic for your node in one set of source files(MinimalSubscriber in our case), but avoid creating any executors or calling spin anywhere. And in a separate file (main.cpp in our case), we can have function which creates an executor, creates an instance of a node, adds node to the executor, and then calls spin().
