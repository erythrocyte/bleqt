#include "bleapp.hpp"

gui::BleApplication::BleApplication()
{
    std::shared_ptr<Hypodermic::ContainerBuilder> builder;

    // What we say here is: when I need an IMessageSerializer,
    // // I want you to use this implementation.
    // builder.registerType<LengthPrefixedMessageSerializer>()
    //     .as<IMessageSerializer>();

    // builder.registerType<ConsoleMessageWriter>().as<IMessageWriter>();

    // Actually build the `Container` we have just configured.
    m_container = builder->build();
}

gui::BleApplication::~BleApplication()
{
}

void gui::BleApplication::run()
{
    // // Container, give us an instance of `IMessageWriter`.
    // auto messageWriter = m_container->resolve<IMessageWriter>();

    // // Alright then, we can write some message.
    // messageWriter->write("The app is running");
}
