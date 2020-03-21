#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class OpenSignEditor : public BaseMessage<OpenSignEditor>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x2A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x2F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x30;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Open Signe Editor";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }


        const NetworkPosition& GetLocation() const
        {
            return location;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();

            return value;
        }

    private:
        NetworkPosition location;

    };
} //ProtocolCraft