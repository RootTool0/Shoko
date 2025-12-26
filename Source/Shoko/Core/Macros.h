#pragma once

#define SHOKO_STATIC_ASSERT(Condition, Message) static_assert(Condition, "\n\'\n[Shoko]\n" Message "\n")

#define SHOKO_GENERATED_BODY() public: static constexpr GUTID_t GUTID = __COUNTER__;

// GUTID - Globally Unique Type Identifier
// Я знаю, звучит странно - но мне нравится
