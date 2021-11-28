@echo off
:: Test using luajit
cd src-lua
luajit test.lua | cd ..
cd ..