#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dict.h"

int testBasic() {
	printf("tests basic\n");
	Dict* dict = createDict();
	addItem(dict, "hello", "world");
	Item* item = getItem(dict, "hello");
	assert(strcmp("hello", item->key) == 0);
	assert(strcmp("world", item->value) == 0);

	addItem(dict, "something", "else");
	item = getItem(dict, "something");
	assert(strcmp("something", item->key) == 0);
	assert(strcmp("else", item->value) == 0);

	addItem(dict, "foo", "bar");
	item = getItem(dict, "foo");
	assert(strcmp("foo", item->key) == 0);
	assert(strcmp("bar", item->value) == 0);

	addItem(dict, "bar", "foo");
	item = getItem(dict, "bar");
	assert(strcmp("bar", item->key) == 0);
	assert(strcmp("foo", item->value) == 0);

	addItem(dict, "ab", "cd");
	item = getItem(dict, "ab");
	assert(strcmp("ab", item->key) == 0);
	assert(strcmp("cd", item->value) == 0);

	addItem(dict, "abcd", "cd");
	item = getItem(dict, "abcd");
	assert(strcmp("abcd", item->key) == 0);
	assert(strcmp("cd", item->value) == 0);

	addItem(dict, "abc", "acd");
	item = getItem(dict, "abc");
	assert(strcmp("abc", item->key) == 0);
	assert(strcmp("acd", item->value) == 0);

	deleteItem(dict, "abc");
	item = getItem(dict, "abc");
	assert(item == 0);

	freeDict(dict);
}

int main() {
	testBasic();
	return 0;
}

