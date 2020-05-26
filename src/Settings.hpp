#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__
class Settings
{
private:
  char *_password;
  char *_ssid;

public:
  const char *password() const
  {
    return _password;
  }
  
  const char *ssid() const
  {
    return _ssid;
  }

  void ssid(const char *value)
  {
    if (value == nullptr)
      _ssid = nullptr;
    else
      _ssid = strdup(value);
  }

  void password(const char *value)
  {
    if (value == nullptr)
      _password = nullptr;
    else
      _password = strdup(value);
  }

  void ssid(const String &value)
  {
    ssid(value.c_str());
  }

  void password(const String &value)
  {
    password(value.c_str());
  }

  bool readFromEEPROM();

  void clearEEPROM();

  void saveToEEPROM();
};
#endif