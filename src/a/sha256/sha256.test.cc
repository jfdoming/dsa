#include "sha256.test.h"

#include <iostream>
#include <vector>

#include "test.h"
#include "a/sha256/sha256.h"

using namespace std;

// Many thanks to https://emn178.github.io/online-tools/sha256.html for
// the SHA256 tool, used to generate the hashes in this test.
void sha256_test() {
    TEST_ASSERT_EQUAL(
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
            sha256("")
    );
    TEST_ASSERT_EQUAL(
            "c0535e4be2b79ffd93291305436bf889314e4a3faec05ecffcbb7df31ad9e51a",
            sha256("Hello world!")
    );
    TEST_ASSERT_EQUAL(
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
            sha256("abc")
    );
    TEST_ASSERT_EQUAL(
            "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
            sha256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq")
    );
    TEST_ASSERT_EQUAL(
            "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1",
            sha256("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu")
    );
    TEST_ASSERT_EQUAL(
            "f506898cc7c2e092f9eb9fadae7ba50383f5b46a2a4fe5597dbb553a78981268",
            sha256(std::string(62, 'a'))
    );
    TEST_ASSERT_EQUAL(
            "7d3e74a05d7db15bce4ad9ec0658ea98e3f06eeecf16b4c6fff2da457ddc2f34",
            sha256(std::string(63, 'a'))
    );
    TEST_ASSERT_EQUAL(
            "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb",
            sha256(std::string(64, 'a'))
    );
    TEST_ASSERT_EQUAL(
            "635361c48bb9eab14198e76ea8ab7f1a41685d6ad62aa9146d301d4f17eb0ae0",
            sha256(std::string(65, 'a'))
    );
    TEST_ASSERT_EQUAL(
            "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0",
            sha256(std::string(1000000, 'a'))
    );
}
