"%wix%"\bin\heat dir Fang -gg -sfrag -cg FangFilesGroup -dr INSTALLDIR -b Fang -out directory.wxs
"%wix%"\bin\candle ../../fang.wxs directory.wxs
"%wix%"\bin\light fang.wixobj directory.wixobj -b Fang -o Fang.msi
