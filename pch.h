#pragma once

#include <Windows.h>
#undef GetCurrentTime
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>

// This is a helper macro for both declaring the signature of a callback (nee event) and
// defining the body. Winrt callbacks need a method for adding a delegate to the
// callback and removing the delegate. This macro will both declare the method
// signatures and define them both for you, because they don't really vary from
// event to event.
// Use this in a class's header if you have a "delegate" type in your IDL.
#define WINRT_CALLBACK(name, args)                                                          \
public:                                                                                     \
    winrt::event_token name(const args& handler) { return _##name##Handlers.add(handler); } \
    void name(const winrt::event_token& token) { _##name##Handlers.remove(token); }         \
                                                                                            \
protected:                                                                                  \
    winrt::event<args> _##name##Handlers;
