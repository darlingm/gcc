
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_Spring$3__
#define __javax_swing_Spring$3__

#pragma interface

#include <javax/swing/Spring.h>
extern "Java"
{
  namespace java
  {
    namespace awt
    {
        class Component;
    }
  }
  namespace javax
  {
    namespace swing
    {
        class Spring$3;
    }
  }
}

class javax::swing::Spring$3 : public ::javax::swing::Spring
{

public: // actually package-private
  Spring$3(::java::awt::Component *);
public:
  virtual jint getMaximumValue();
  virtual jint getMinimumValue();
  virtual jint getPreferredValue();
  virtual jint getValue();
  virtual void setValue(jint);
private:
  ::java::awt::Component * __attribute__((aligned(__alignof__( ::javax::swing::Spring)))) val$component;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_Spring$3__
