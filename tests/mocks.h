#pragma once

#include <string>
#include <vector>
#include <gmock/gmock.h>
#include "IHistory.h"

namespace calc {

    // Мок истории — для проверки, что калькулятор действительно вызывает AddEntry()
    class MockHistory : public IHistory {
    public:
        MOCK_METHOD(void, AddEntry, (const std::string& operation), (override));
        // GetLastOperations нам в моках обычно не нужен, но можно:
        MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t count), (const, override));
    };

} // namespace calc