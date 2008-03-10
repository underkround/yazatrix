#ifndef __MENU_H__
#define __MENU_H__

#define itemcount 2

class CTetrisMenu {
  public:
  CTetrisMenu(void);
  ~CTetrisMenu(void);
  private:
  char* m_chrMenuItems[2];

  void CreateMenu(void);

};

#endif //__MENU_H__
