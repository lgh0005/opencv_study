#pragma once

/*===========================//
//     Class Constraints     //
//===========================*/
#define DISABLE_COPY(className)                                       \
    className(const className&) = delete;                             \
    className& operator=(const className&) = delete;

#define DISABLE_MOVE(className)                                       \
    className(className&&) = delete;                                  \
    className& operator=(className&&) = delete;

/*===============================//
//     Singleton Declaration     //
//===============================*/
#define DECLARE_SINGLE(className)                                     \
private:                                                              \
    DISABLE_COPY(className)                                           \
    DISABLE_MOVE(className)                                           \
                                                                      \
public:                                                               \
    static className& Instance()                                      \
    {                                                                 \
        static className* s_instance = new className();               \
        return *s_instance;                                           \
    }