﻿// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "AppAppearanceConfig.h"

#include "AppAppearanceConfig.g.cpp"

using namespace winrt::Microsoft::Terminal;
using namespace winrt::TerminalApp;
using namespace winrt::Microsoft::Terminal::TerminalControl;

namespace winrt::TerminalApp::implementation
{
    // Method Description:
    // - Apply a given ColorScheme's values to the AppAppearanceConfig object.
    //      Sets the foreground, background, and color table of the settings object.
    // - This is the same as TerminalSettings::ApplyColorScheme, but for AppAppearanceConfig
    // Arguments:
    // - scheme: the ColorScheme we are applying to the TerminalSettings object
    void AppAppearanceConfig::ApplyColorScheme(const Microsoft::Terminal::Settings::Model::ColorScheme& scheme)
    {
        _DefaultForeground = til::color{ scheme.Foreground() };
        _DefaultBackground = til::color{ scheme.Background() };
        _SelectionBackground = til::color{ scheme.SelectionBackground() };
        _CursorColor = til::color{ scheme.CursorColor() };

        const auto table = scheme.Table();
        std::transform(table.cbegin(), table.cend(), _colorTable.begin(), [](auto&& color) {
            return static_cast<uint32_t>(til::color{ color });
        });
    }

    uint32_t AppAppearanceConfig::GetColorTableEntry(int32_t index) const noexcept
    {
        return _colorTable.at(index);
    }
}
