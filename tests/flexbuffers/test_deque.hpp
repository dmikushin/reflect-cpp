#include <iostream>
#include <rfl.hpp>
#include <rfl/flexbuf.hpp>
#include <string>
#include <vector>

#include "write_and_read.hpp"

void test_deque() {
    std::cout << "test_deque" << std::endl;

    struct Person {
        rfl::Field<"firstName", std::string> first_name;
        rfl::Field<"lastName", std::string> last_name = "Simpson";
        rfl::Field<"children", std::unique_ptr<std::deque<Person>>> children =
            rfl::default_value;
    };

    auto children = std::make_unique<std::deque<Person>>();
    children->emplace_back(Person{.first_name = "Bart"});
    children->emplace_back(Person{.first_name = "Lisa"});
    children->emplace_back(Person{.first_name = "Maggie"});

    const auto homer =
        Person{.first_name = "Homer", .children = std::move(children)};

    write_and_read(homer);
}