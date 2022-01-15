// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <cstddef>
#include <atomic>

template <typename T>
class SharedPtr {
 private:
  T* pw;
  std::atomic_uint* count;
 public:
  SharedPtr(){
    pw = nullptr;
    count = nullptr;
  };
  SharedPtr(T* ptr){
    pw = ptr;
    count = new std::atomic_uint(1);
  };
  SharedPtr(const SharedPtr& r){
    pw = r.pw;
    count = r.count;
    (*count)++;
  };
  SharedPtr(SharedPtr&& r){
    pw = r.pw;
    count = r.count;
    r.pw = nullptr;
    r.count = nullptr;
  };
  ~SharedPtr(){
    if (count != nullptr) {
      if((*count) == 1) {
        delete pw;
        delete count;
      }else (*count)--;
    }
  };
  auto operator=(const SharedPtr& r) -> SharedPtr&{
      if (*this != r){
        if (count != nullptr) {
          if (*count == 1) {
            delete pw;
            delete count;
          } else
            (*count)--;
        }
        pw = r.pw;
        count = r.count;
        (*count)++;
      }
    return *this;
  };
  auto operator=(SharedPtr&& r) -> SharedPtr&{
    if (*this != r){
      if (count != nullptr) {
        if (*count == 1) {
          delete pw;
          delete count;
        } else
          (*count)--;
      }
      pw = r.pw;
      count = r.count;
      r.pw = nullptr;
      r.count = nullptr;
    }
    return *this;
  };

  // проверяет, указывает ли указатель на объект
  operator bool() const{
      return (pw != nullptr);
  };
  auto operator*() const -> T&{
      return *pw;
  };
  auto operator->() const -> T*{
      return pw;
  };

  auto get() -> T*{
    return pw;
  }
  void reset(){
      if (pw != nullptr){
        if((*count)==1){
          delete pw;
          delete count;
        }
      }
      pw = nullptr;
      count = nullptr;
  };
  void reset(T* ptr){
      if (pw != nullptr){
        if ((*count)==1){
          delete pw;
          delete count;
        }else (*count)--;
      }
      pw = ptr;
      count = new std::atomic_uint();
    (*count)++;
  };
  void swap(SharedPtr& r){
      std::swap(pw, r.pw);
      std::swap(count, r.count);
  };
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
  auto use_count() const -> size_t{
    if (count != nullptr) {
      return *count;
    } else return 0;
  }
};

#endif // INCLUDE_HEADER_HPP_
