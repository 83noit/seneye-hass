SOURCE_DIR := src
TEST_DIR := test

.PHONY: format

format: SHELL := /bin/zsh
format:
	clang-format -i {$(SOURCE_DIR),$(TEST_DIR)}/**/*{.cpp,.h}(N)

