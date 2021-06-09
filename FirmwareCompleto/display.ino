void display(String Texto1,int x1, int y1,String Texto2,int x2, int y2,String Texto3,int x3, int y3,String Texto4,int x4, int y4,String Texto5,int x5, int y5){
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(x1,y1, Texto1.c_str());
    u8g2.drawStr(x2,y2, Texto2.c_str());
    u8g2.drawStr(x3,y3, Texto3.c_str());
    u8g2.drawStr(x4,y4, Texto4.c_str());
    u8g2.drawStr(x5,y5, Texto5.c_str());
  } while ( u8g2.nextPage() );
}
