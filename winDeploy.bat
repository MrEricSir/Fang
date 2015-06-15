@echo on
heat dir Fang -gg -sfrag -cg FangFilesGroup -dr INSTALLDIR -b Fang -out directory.wxs
candle ../../fang.wxs directory.wxs
light fang.wixobj directory.wixobj -b Fang -o Fang.msi
