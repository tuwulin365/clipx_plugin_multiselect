#ifndef _MEMBLOCK_H
#define _MEMBLOCK_H

#include <bfc/std.h>
#include <wasabicfg.h>

#ifdef WASABI_DEBUG
extern int memblocks_totalsize;
#endif

class COMEXP VoidMemBlock {
protected:
  VoidMemBlock(int size=0, const void *data=NULL);
  ~VoidMemBlock();

  void *setSize(int newsize);
  void *setMinimumSize(int newminsize, int increment=0);
  void *getMemory() const { return mem; }
  void setMemory(const void *data, int datalen, int offsetby=0);
  int getSize() const;

  int isMine(void *ptr);

  void zeroMemory();

private:
  void *mem;
  int size;
};

// just a convenient resizeable block of memory wrapper
// doesn't handle constructors or anything, meant for int, char, etc.
template <class T>
class MemBlock : private VoidMemBlock {
public:
  MemBlock(int _size = 0, const T *data = NULL) : VoidMemBlock(_size*sizeof(T), data) {}
  MemBlock(const MemBlock<T> &source) : VoidMemBlock(source.getSizeInBytes(), source.getMemory()) {}
  MemBlock(const MemBlock<T> *source) : VoidMemBlock(source->getSizeInBytes(), source->getMemory()) {}

  T *setSize(int newsize) {
    return static_cast<T*>(VoidMemBlock::setSize(newsize * sizeof(T)));
  }
  T *setMinimumSize(int newminsize, int increment = 0) {
    return static_cast<T*>(VoidMemBlock::setMinimumSize(newminsize * sizeof(T), increment*sizeof(T)));
  }

  T *getMemory() const { return static_cast<T *>(VoidMemBlock::getMemory()); }
  T *getMemory(int offset) const { return static_cast<T *>(VoidMemBlock::getMemory())+offset; } // note pointer arithmetic
  T *m() const { return getMemory(); }
  T *m(int offset) const { return getMemory(offset); }
  operator T *() const { return getMemory(); }
  T& operator() (unsigned int ofs) { return getMemory()[ofs]; }
  const T& operator() (unsigned int ofs) const { return getMemory()[ofs]; }
  int isNull() const { return (getMemory() == NULL); }

  void copyTo(T *dest) { MEMCPY(getMemory(), dest, getSizeInBytes()); }

  int getSize() const { return VoidMemBlock::getSize()/sizeof(T); }// # of T's
  int getSizeInBytes() const { return VoidMemBlock::getSize(); }

  int isMine(T *ptr) { return VoidMemBlock::isMine(ptr); }

  void setMemory(const T *data, int datalen, int offsetby = 0) { VoidMemBlock::setMemory(data, datalen*sizeof(T), offsetby*sizeof(T)); }	// # of T's
  void zeroMemory() { VoidMemBlock::zeroMemory(); }

  void reverse() {
    const int nitems = getSize();
    if (nitems <= 1) return;
    MemBlock<T> nm(this);
    T *mymem = getMemory(), *revmem = nm.getMemory();
    for (int i = 0, j = nitems-1; j >= 0; i++, j--) {
      MEMCPY(mymem+i, revmem+j, sizeof(T));
    }
  }
};

// just a convenience class for a 2d MemBlock<>
template <class T>
class MemMatrix : public MemBlock<T> {
public:
  MemMatrix(int _width=0, int _height=0, const T *data = NULL) :
    MemBlock<T>(_width * _height, data), width(_width), height(_height) {}

  T *setSize(int _width, int _height) {
    MemBlock<T>::setSize(_width * _height);
    width = _width;
    height = _height;
    return MemBlock<T>::getMemory();
  }

  int getWidth() const { return width; }
  int getHeight() const { return height; }

  // () access i.e. obj(x,y)
  T& operator() (unsigned int x, unsigned int y) {
    return *MemBlock<T>::m(x + y * width);
  }
  const T& operator() (unsigned int x, unsigned int y) const {
    return *MemBlock<T>::m(x + y * width);
  }
  T& getRef(unsigned int x, unsigned int y) {
    return *MemBlock<T>::m(x + y * width);
  }
  T* m2(int x=0, int y=0) const { return m(y*width+x); }

private:
  int width, height;
};


#endif
