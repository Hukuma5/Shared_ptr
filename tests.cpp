// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <vector>
#include <header.hpp>

TEST (SharedPtr, empty){
  SharedPtr<int> p;
  EXPECT_EQ(p.get(), nullptr);
  EXPECT_EQ(p.use_count(), 0);
}

TEST(SharedPtr, only_ptr){
  int* i = new int(5);
  SharedPtr<int> p1(i);
  EXPECT_EQ(p1.get(), i);
  EXPECT_EQ(p1.use_count(), 1);
}

TEST(SharedPtr, with_link){
  int* i = new int(5);
  SharedPtr<int> p1(i);
  SharedPtr<int> p2(p1);
  EXPECT_EQ(p1.get(), p2.get());
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(p2.use_count(), 2);
}

TEST(SharedPtr, with_2links){
  int* i = new int(5);
  SharedPtr<int> p1(i);
  SharedPtr<int> p2(std::move(p1));
  EXPECT_EQ(p2.get(), i);
  EXPECT_EQ(p2.use_count(), 1);
  EXPECT_EQ(p1.get(), nullptr);
  EXPECT_EQ(p1.use_count(), 0);
}

TEST(SharedPtr, equality){
  int* i = new int(10);
  SharedPtr<int> p1(i);
  SharedPtr<int> p2;
  p2 = p1;
  SharedPtr<int> p3;
  p3 = std::move(p1);
  EXPECT_EQ(p2.get(), i);
  EXPECT_EQ(p2.use_count(), 2);
  EXPECT_EQ(p3.get(), i);
  EXPECT_EQ(p3.use_count(), 2);
  EXPECT_EQ(p1.get(), nullptr);
  EXPECT_EQ(p1.use_count(), 0);
}

TEST(SharedPtr, boolean){
  int* i = new int(10);
  SharedPtr<int> p1(i);
  SharedPtr<int> p2;
  EXPECT_EQ((p1), true);
  EXPECT_EQ((p2), false);
}

TEST(SharedPtr, other_operartors){
  int* i = new int(5);
  SharedPtr<int> p1(i);
  std::string* str = new std::string("qwerty");
  SharedPtr<std::string> p2(str);
  EXPECT_EQ(*p1, 5);
  EXPECT_EQ(*p2, "qwerty");
  EXPECT_EQ(p2->size(), 6);
}

TEST(SharedPtr, reset){
  int* i = new int(5);
  SharedPtr<int> p1(i);
  p1.reset();
  EXPECT_EQ(p1.get(), nullptr);
  EXPECT_EQ(p1.use_count(), 0);
  int* j = new int(5);
  p1.reset(j);
  EXPECT_EQ(p1.get(), j);
  EXPECT_EQ(p1.use_count(), 1);
}

TEST(SharedPtr, swap){
  int* i = new int (5);
  SharedPtr<int> p1(i);
  SharedPtr<int> p2(p1);
  SharedPtr<int> p3;
  p2.swap(p3);
  EXPECT_EQ(p2.get(), nullptr);
  EXPECT_EQ(p3.get(), i);
  EXPECT_EQ(p2.use_count(), 0);
  EXPECT_EQ(p3.use_count(), 2);
}
