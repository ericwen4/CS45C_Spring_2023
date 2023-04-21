#include <gtest/gtest.h>

#include <sstream>

#include "string.hpp"

using namespace std;

TEST(StringClass, EmptyConstructors) {
    String s, t;

    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s, t);

    String x("");
    EXPECT_EQ(s, x);
    EXPECT_EQ(x.size(), 0);
}

TEST(StringClass, Constructors) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);

    String t(s);
    EXPECT_EQ(t.size(), 5);
    EXPECT_EQ(s.size(), 5);
}

TEST(StringClass, Assignment) {
    String s("test"), t("foo");

    s = t;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = s;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = String();
    EXPECT_EQ(s, String());
    EXPECT_EQ(s.size(), 0);
}

TEST(StringClass, Reverse) {
    String s("foo");

    EXPECT_EQ(s.reverse(), String("oof"));
    EXPECT_EQ(String("").reverse(), String(""));
}

TEST(StringClass, IndexOfChar) {
    String haystack("abcdefghkl");
    EXPECT_EQ(haystack.indexOf('a'), 0);
    EXPECT_EQ(haystack.indexOf('b'), 1);
    EXPECT_EQ(haystack.indexOf('c'), 2);
    EXPECT_EQ(haystack.indexOf('z'), -1);
}

TEST(StringClass, IndexOfString) {
    String haystack("foofooofoooofooooo");
    EXPECT_EQ(haystack.indexOf(String("fooooooo")), -1);
    EXPECT_EQ(haystack.indexOf(String("foo")), 0);
    EXPECT_EQ(haystack.indexOf(String("")), 0);
    EXPECT_EQ(haystack.indexOf(String("fooo")), 3);
}

TEST(StringClass, Comparisons) {
    EXPECT_LT(String("aaaa"), String("aaab"));
    EXPECT_LE(String("aaaa"), String("aaab"));
    EXPECT_EQ(String("foo"), String("foo"));
    EXPECT_NE(String("foo"), String("fooo"));
    EXPECT_LT(String("asdf"), String("asdf!"));
    EXPECT_LT(String(""), String("a"));
    EXPECT_GT(String("haha"), String("hah"));
    EXPECT_GE(String("haha"), String("hah"));
    EXPECT_GT(String("z"), String("a"));
    EXPECT_GE(String("a"), String("a"));
}

TEST(StringClass, Plus) {
    String s("test");
    String t("ing");
    s += t;
    EXPECT_EQ(s, String("testing"));
    EXPECT_EQ(s += s, String("testingtesting"));

    EXPECT_EQ(String("foo") + String("bar"), String("foobar"));
    EXPECT_EQ(String("foo") + String(""), String("foo"));
    EXPECT_EQ(String("") + String("foo"), String("foo"));
}

TEST(StringClass, Print) {
    String s("foo");
    stringstream out;
    s.print(out);
    EXPECT_STREQ(out.str().c_str(), "foo");

    stringstream out2;
    String().print(out2);
    EXPECT_STREQ(out2.str().c_str(), "");

    stringstream out3;
    out3 << s << s << String("bar");
    EXPECT_STREQ(out3.str().c_str(), "foofoobar");
}

TEST(StringClass, Read) {
    stringstream in("foo bar hello world");
    String foo, bar, hello, world;
    foo.read(in);
    bar.read(in);
    in >> hello >> world;

    EXPECT_EQ(foo, String("foo"));
    EXPECT_EQ(bar, String("bar"));
    EXPECT_EQ(hello, String("hello"));
    EXPECT_EQ(world, String("world"));
}
