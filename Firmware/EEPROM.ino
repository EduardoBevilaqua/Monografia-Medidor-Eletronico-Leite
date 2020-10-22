void gravarEeprom(int value, int pos) {
   EEPROM.write(pos, 0);
   EEPROM.write(pos + 1, 0);
   byte hiByte = highByte(value);
   byte loByte = lowByte(value);

   EEPROM.write(pos, hiByte);
   EEPROM.write(pos + 1, loByte);   
}

int lerEeprom(int pos) {
   byte hiByte = EEPROM.read(pos);
   byte loByte = EEPROM.read(pos + 1);
   
   return word(hiByte, loByte); 
}
