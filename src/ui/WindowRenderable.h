#ifndef _WINDOW_RENDERABLE_H_
#define _WINDOW_RENDERABLE_H_
template<typename Event>
class WindowRenderable
{
 public:
  virtual void render ()
  {};
  virtual void update ()
  {};
  virtual void handle_event (Event *)
  {};
};

#endif
