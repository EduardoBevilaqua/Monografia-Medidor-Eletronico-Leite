void gravarEeprom(int value, int pos) {
   display("Gravando Valor = ", 5, 5,String(value),5,60,"",0,0,"",0,0,"",0,0);
   delay(100);
   EEPROM.begin(1024);
   EEPROM.write(pos, 0);
   EEPROM.write(pos + 1, 0);
   byte hiByte = highByte(value);
   byte loByte = lowByte(value);
   EEPROM.write(pos, hiByte);
   EEPROM.commit();
   EEPROM.write(pos + 1, loByte);  
   EEPROM.commit(); 
   EEPROM.end();
}
int lerEeprom(int pos) {
   EEPROM.begin(1024);
   byte hiByte = EEPROM.read(pos);
   byte loByte = EEPROM.read(pos + 1);
   EEPROM.end();
   int saida = word(hiByte, loByte);
   return saida; 
}
