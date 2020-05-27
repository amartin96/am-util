#include <AMUtil/DebugObject.h>

#include <iostream>


namespace AMUtil {
    std::function<void(std::size_t, const std::string&)> DebugObject::onConstructor
    = [](std::size_t id, const std::string& name) {
        std::cout << "DebugObject id=" << id << " name=" << name << " constructed" << std::endl;
    };

    std::function<void(std::size_t, std::size_t, const std::string&)> DebugObject::onCopyConstructor
    = [](std::size_t oldId, std::size_t newId, const std::string& name) {
        std::cout << "DebugObject id=" << newId << " name=" << name << " copy-constructed from id=" << oldId << std::endl;
    };

    std::function<void(std::size_t, std::size_t, const std::string&)> DebugObject::onMoveConstructor
    = [](std::size_t oldId, std::size_t newId, const std::string& name) {
        std::cout << "DebugObject id=" << newId << " name=" << name << " move-constructed from id=" << oldId << std::endl;
    };

    std::function<void(std::size_t, const std::string&)> DebugObject::onDestructor
    = [](std::size_t id, const std::string& name) {
        std::cout << "DebugObject id=" << id << " name=" << name << " destroyed" << std::endl;
    };

    std::function<void(std::size_t, const std::string&, std::size_t, const std::string&)> DebugObject::onCopyAssignment
    = [](std::size_t oldId, const std::string& oldName, std::size_t newId, const std::string& newName) {
        std::cout << "DebugObject id=" << newId << " name=" << newName << " copy-assigned from id=" << oldId << " name=" << oldName << std::endl;
    };

    std::function<void(std::size_t, const std::string&, std::size_t, const std::string&)> DebugObject::onMoveAssignment
    = [](std::size_t oldId, const std::string& oldName, std::size_t newId, const std::string& newName) {
        std::cout << "DebugObject id=" << newId << " name=" << newName << " move-assigned from id=" << oldId << " name=" << oldName << std::endl;
    };

    std::function<void(std::size_t, const std::string&)> DebugObject::onCall
    = [](std::size_t id, const std::string& name) {
        std::cout << "DebugObject id=" << id << " name=" << name << " called" << std::endl;
    };

    DebugObject::DebugObject(const std::string& name) : name(name) {
        DebugObject::lock.lock();
        this->id = DebugObject::count++;
        DebugObject::lock.unlock();

        DebugObject::onConstructor(this->id, this->name);
    }

    DebugObject::DebugObject(std::string&& name) : name(std::move(name)) {
        DebugObject::lock.lock();
        this->id = DebugObject::count++;
        DebugObject::lock.unlock();

        DebugObject::onConstructor(this->id, this->name);
    }

    DebugObject::DebugObject(const DebugObject& other) : name(other.name) {
        DebugObject::lock.lock();
        this->id = DebugObject::count++;
        DebugObject::lock.unlock();

        DebugObject::onCopyConstructor(other.id, this->id, this->name);
    }

    DebugObject::DebugObject(DebugObject&& other) : name(std::move(other.name)) {
        DebugObject::lock.lock();
        this->id = DebugObject::count++;
        DebugObject::lock.unlock();

        DebugObject::onMoveConstructor(other.id, this->id, this->name);
    }

    DebugObject::~DebugObject() {
        DebugObject::onDestructor(this->id, this->name);
    }

    DebugObject& DebugObject::operator=(const DebugObject& other) {
        DebugObject::onCopyAssignment(other.id, other.name, this->id, this->name);
        this->name = other.name;
    }

    DebugObject& DebugObject::operator=(DebugObject&& other) {
        DebugObject::onCopyAssignment(other.id, other.name, this->id, this->name);
        this->name = std::move(other.name);
    }

    void DebugObject::operator()() {
        DebugObject::onCall(this->id, this->name);
    }
}
