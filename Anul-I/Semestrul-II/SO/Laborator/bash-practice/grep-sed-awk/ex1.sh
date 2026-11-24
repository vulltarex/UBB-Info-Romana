#!/bin/bash

grep -E "economica(.)*Sun" last.fake | awk {'print $1'} | sort | uniq
