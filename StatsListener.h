#ifndef __STATSLISTENER_H__
#define __STATSLISTENER_H__

class VStatsListener {

public:

  virtual void handleChangeInStats(const int score, const int level, const int reml, const int remll) = 0;

};

#endif // __STATSLISTENER_H__
