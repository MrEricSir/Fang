@echo on
set /p IN_VERSION=<..\APP_VERSION
echo "##teamcity[setParameter name='APP_VERSION' value='%IN_VERSION%']"
