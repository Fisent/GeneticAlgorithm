#!/usr/bin/env bash
rm charts/ps*
mv ../bin/ps* ./charts
./generate
