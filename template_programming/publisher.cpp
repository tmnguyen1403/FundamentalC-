#include <iostream>
//Publisher class
//This allow the Tracker not depend on the publisher
//The Publisher can be free to implement
//How is this different than having interface through inheritance?

class Publisher
{
public:
    Publisher(){std::cout << "construct publisher\n";}
    Publisher(const Publisher& publisher){std::cout << "copy constructor\n";}
    template <typename... Args>
    void publish(Args... args){
        std::cout << "Publishing this many args\n";
    //Counter can be added here
    }

};
template<>
void Publisher::publish(int a,double b,int c) {
    std::cout << "Specialized for a,b,c,\n";
}

template <typename PublisherT>
class Tracker
{
public:
    void create_publisher(const std::shared_ptr<PublisherT>& publisher)
    {
        std::cout << "ref count b: " << publisher.use_count() << std::endl;
        publisher_ = publisher;
        std::cout << "ref count e: " << publisher.use_count() << std::endl;

    }
    void process(int a, double b, int c)
    {
        if (publisher_ != nullptr)
            publisher_->publish(a,b,c);
        else
            std::cout << "no publisher to publish\n";
    }
private:
    std::shared_ptr<PublisherT> publisher_;
};

int main()
{
    Tracker<Publisher> tracker{};
    tracker.process(1,2.0,3);
    auto publisher = std::make_shared<Publisher>();
    std::cout << "ref count: " << publisher.use_count() << std::endl;
    tracker.create_publisher(publisher);
    std::cout << "ref count a: " << publisher.use_count() << std::endl;

    tracker.process(1,2.0,3);
    std::cout <<"Hello world\n";
    return 0;
}