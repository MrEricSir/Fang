@echo on
REM This sets the version in TeamCity
set /p IN_VERSION=<..\APP_VERSION
echo "##teamcity[setParameter name='env.APP_VERSION' value='%IN_VERSION%']"
