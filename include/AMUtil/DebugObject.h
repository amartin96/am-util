#pragma once

#include <functional>
#include <mutex>
#include <string>


namespace AMUtil {
    class DebugObject {
    public:
        /// Called when a named DebugObject instance is constructed.
        /// \param 0    The id of the instance
        /// \param 1    The name of the instance
        static std::function<void(std::size_t, const std::string&)> onConstructor;

        /// Called when a DebugObject instance is copy-constructed.
        /// \param 0    The id of the old instance
        /// \param 1    The id of the new instance
        /// \param 2    The name, the same for both instances
        static std::function<void(std::size_t, std::size_t, const std::string&)> onCopyConstructor;

        /// Called when a DebugObject instance is move-constructed.
        /// \param 0    The id of the old instance
        /// \param 1    The id of the new instance
        /// \param 2    The name, the same for both instances
        static std::function<void(std::size_t, std::size_t, const std::string&)> onMoveConstructor;

        /// Called when a DebugObject instance is destroyed.
        /// \param 0    The id of the instance
        /// \param 1    The name of the instance
        static std::function<void(std::size_t, const std::string&)> onDestructor;

        /// Called when a DebugObject instance is copy-assigned.
        /// \param 0    The id of the old instance
        /// \param 1    The name of the old instance
        /// \param 2    The id of the new instance
        /// \param 3    The name of the new instance
        static std::function<void(std::size_t, const std::string&, std::size_t, const std::string&)> onCopyAssignment;

        /// Called when a DebugObject instance is move-assigned.
        /// \param 0    The id of the old instance
        /// \param 1    The name of the old instance
        /// \param 2    The id of the new instance
        /// \param 3    The name of the new instance
        static std::function<void(std::size_t, const std::string&, std::size_t, const std::string&)> onMoveAssignment;

        /// Called when DebugObject::operator() is called.
        /// \param 0    The id of the instance
        /// \param 1    The name of the instance
        static std::function<void(std::size_t, const std::string&)> onCall;

        DebugObject(const std::string& name);
        DebugObject(std::string&& name = "");
        DebugObject(const DebugObject& other);
        DebugObject(DebugObject&& other);
        
        ~DebugObject();

        DebugObject& operator=(const DebugObject& other);
        DebugObject& operator=(DebugObject&& other);

        void operator()();
    
    private:
        static std::mutex lock;
        static inline std::size_t count = 0;

        std::size_t id;
        std::string name;
    };
}
