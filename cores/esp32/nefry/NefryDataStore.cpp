/**
Nefry lib

Copyright (c) 2015 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryDataStore.h"


void NefryDataStore_lib::begin()
{
	nefryDataStorePreferences = Preferences();
	nefryDataStorePreferences.begin("nefryStore");
}
/*
void NefryDataStore_lib::clear()
{
	nefryDataStorePreferences.clear();
}
*/

bool NefryDataStore_lib::setModuleID(String id)
{
	return nefryDataStorePreferences.putString("ModuleID",id);
}

bool NefryDataStore_lib::setBootSelector(int mode)
{
	return nefryDataStorePreferences.putInt("BootSelector", mode);
}

bool NefryDataStore_lib::setConnectPass(String str, int pointer)
{
	String key;
	key = "ConnectPass";
	key += pointer;
	return nefryDataStorePreferences.putString(key.c_str(), str);
}

bool NefryDataStore_lib::setConnectSSID(String str, int pointer)
{
	String key;
	key = "ConnectSSID";
	key += pointer;
	return nefryDataStorePreferences.putString(key.c_str(), str);
}

bool NefryDataStore_lib::setStorageStr(String str, int pointer)
{
	String key;
	key = "StorageStr";
	key += pointer;
	return nefryDataStorePreferences.putString(key.c_str(), str);
}

bool NefryDataStore_lib::setStorageValue(long value, int pointer)
{
	String key;
	key = "StorageValue";
	key += pointer;
	return nefryDataStorePreferences.putLong(key.c_str(), value);
}

bool NefryDataStore_lib::setUserPass(String pass)
{
	return nefryDataStorePreferences.putString("UserPass", pass);
}

bool NefryDataStore_lib::setUser(String user)
{
	return nefryDataStorePreferences.putString("User", user);
}

bool NefryDataStore_lib::setModuleClass(String className)
{
	return nefryDataStorePreferences.putString("ModuleClass", className);
}

bool NefryDataStore_lib::setModulePass(String pass)
{
	return nefryDataStorePreferences.putString("ModulePass", pass);
}

/* 取得 */

String NefryDataStore_lib::getModuleID()
{
	return nefryDataStorePreferences.getString("ModuleID","");
}

String NefryDataStore_lib::getConnectPass(int pointer)
{
	String key;
	key = "ConnectPass";
	key += pointer;
	return nefryDataStorePreferences.getString(key.c_str(), "");
}

int NefryDataStore_lib::getBootSelector()
{
	return nefryDataStorePreferences.getInt("BootSelector",0);
}

long NefryDataStore_lib::getStorageValue(int pointer)
{
	String key;
	key = "StorageValue";
	key += pointer;
	return nefryDataStorePreferences.getLong(key.c_str(),0);
}

String NefryDataStore_lib::getConnectSSID(int pointer)
{
	String key;
	key = "ConnectSSID";
	key += pointer;
	return nefryDataStorePreferences.getString(key.c_str(), "");
}

String NefryDataStore_lib::getStorageStr(int pointer)
{
	String key;
	key = "StorageStr";
	key += pointer;
	return nefryDataStorePreferences.getString(key.c_str(), "");
}

String NefryDataStore_lib::getUserPass()
{
	return nefryDataStorePreferences.getString("UserPass", "");
}

String NefryDataStore_lib::getUser()
{
	return nefryDataStorePreferences.getString("User", "");
}

String NefryDataStore_lib::getModuleClass()
{
	return nefryDataStorePreferences.getString("ModuleClass", "");
}

String NefryDataStore_lib::getModulePass()
{
	return nefryDataStorePreferences.getString("ModulePass", "");
}


NefryDataStore_lib NefryDataStore;
