/******************************************************************************
    Copyright (C) 2013 by Hugh Bailey <obs.jim@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#pragma once

#include <QApplication>
#include <QTranslator>
#include <util/util.hpp>
#include <string>
#include <memory>

#include "window-main.hpp"

class OBSTranslator : public QTranslator {
	Q_OBJECT

public:
	virtual bool isEmpty() const override {return false;}

	virtual QString translate(const char *context, const char *sourceText,
			const char *disambiguation, int n) const override;
};

class OBSApp : public QApplication {
	Q_OBJECT

private:
	std::string                    locale;
	ConfigFile                     globalConfig;
	TextLookup                     textLookup;
	std::unique_ptr<OBSMainWindow> mainWindow;

	bool InitGlobalConfig();
	bool InitGlobalConfigDefaults();
	bool InitLocale();

public:
	OBSApp(int &argc, char **argv);

	void OBSInit();

	inline QMainWindow *GetMainWindow() const {return mainWindow.get();}

	inline config_t GlobalConfig() const {return globalConfig;}

	inline const char *GetLocale() const
	{
		return locale.c_str();
	}

	inline lookup_t GetTextLookup() const {return textLookup;}

	inline const char *GetString(const char *lookupVal) const
	{
		return textLookup.GetString(lookupVal);
	}

	std::string GetVersionString() const;

	const char *InputAudioSource() const;
	const char *OutputAudioSource() const;

	const char *GetRenderModule() const;
};

inline OBSApp *App() {return static_cast<OBSApp*>(qApp);}

inline config_t GetGlobalConfig() {return App()->GlobalConfig();}

inline const char *Str(const char *lookup) {return App()->GetString(lookup);}
#define QTStr(lookupVal) QString::fromUtf8(Str(lookupVal))
