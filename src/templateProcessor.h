/**
 * Process template and replace variables 
 */
String processor(const String& var)
{
  if(var == "RED_STATUS") {
    sprintf(statusStr, "%d", redStatus);
    return(statusStr);
  }

  if(var == "YELLOW_STATUS"){
    sprintf(statusStr, "%d", yellowStatus);
    return(statusStr);
  }

  if(var == "GREEN_STATUS") {
    sprintf(statusStr, "%d", greenStatus);
    return(statusStr);
  }

  if(var == "SSID") {
    return(ssid);
  }
  
  if(var == "IP_ADDRESS") {
    return(ipAddress);
  }

  if(var == "AP_NAME") {
    return(apName);
  }

  if(var == "RSSI") {
    return(rssiStr);
  }

  if(var == "MDNS_NAME") {
    return(dnsName);
  }

  if(var == "CHIP_ID") {
    return(chipIdString);
  }

  if(var == "CPU_FREQ") {
    return(cpuFreqString);
  }

  if(var == "FLASH_SIZE") {
    return(flashChipSizeString);
  }

  if(var == "TEMPERATURE") {
    return(String(Temperature));
  }

  if(var == "HUMIDITY") {
    return(String(Humidity));
  }

  if(var == "TIME") {
    return(String(timeStr));
  }

  return String();
}
