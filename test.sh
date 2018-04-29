#!/bin/bash
cmake -P $(dirname $0)/test.cmake $*
