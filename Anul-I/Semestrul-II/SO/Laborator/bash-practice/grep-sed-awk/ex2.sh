#!/bin/bash

grep -E "23:.. -" last.fake | awk {'print $1'} | sort | uniq
